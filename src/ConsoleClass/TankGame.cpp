#include "TankGame.h"
#include "Console.h"

TankGame::TankGame(Console* console) : Game(console)
{

}

TankGame::~TankGame()
{

}

void TankGame::init()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      tanks[i].direction = 0;
      tanks[i].bullet.position.x = NONE;
      tanks[i].bullet.position.y = NONE;
  }
  
  tanks[0].position.x = ONE_S_X;
  tanks[0].position.y = ONE_S_Y;
  tanks[0].color = ColorRGB(C1);
  for(int i = 0;i<ONE_S_R;i++)
      tanks[0].rotate(RIGHT);
  tanks[1].position.x = TWO_S_X;
  tanks[1].position.y = TWO_S_Y;
  tanks[1].color = ColorRGB(C2);
  for(int i = 0;i<TWO_S_R;i++)
      tanks[1].rotate(RIGHT);
  tanks[2].position.x = THREE_S_X;
  tanks[2].position.y = THREE_S_Y;
  tanks[2].color = ColorRGB(C3);
  for(int i = 0;i<THREE_S_R;i++)
      tanks[2].rotate(RIGHT);
  tanks[3].position.x = FOUR_S_X;
  tanks[3].position.y = FOUR_S_Y;
  tanks[3].color = ColorRGB(C4);
  for(int i = 0;i<FOUR_S_R;i++)
      tanks[3].rotate(RIGHT);

  walls[0].position.x = 5;
  walls[0].position.y = 5;
  walls[0].width = 10;
  walls[0].height = 1;
  walls[1].position.x = 10;
  walls[1].position.y = 20;
  walls[1].width = 1;
  walls[1].height = 8;
  walls[2].position.x = 6;
  walls[2].position.y = 20;
  walls[2].width = 1;
  walls[2].height = 8;
  walls[3].position.x = 20;
  walls[3].position.y = 10;
  walls[3].width = 8;
  walls[3].height = 1;
}

void TankGame::update()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      if(tanks[i].bullet.position.x < 0 || tanks[i].bullet.position.x >= WIDTH || tanks[i].bullet.position.y < 0 || tanks[i].bullet.position.y >= HEIGHT)
      {
          tanks[i].bullet.position.x = NONE;
      }
      
      if(tanks[i].bullet.position.x != NONE)
      {
          switch(tanks[i].bullet.direction)
          {
              case DOWN:
                  tanks[i].bullet.position.y+=BULLET_SPEED;
                  break;
              case LEFT:
                  tanks[i].bullet.position.x-=BULLET_SPEED;
                  break;
              case UP:
                  tanks[i].bullet.position.y-=BULLET_SPEED;
                  break;
              case RIGHT:
                  tanks[i].bullet.position.x+=BULLET_SPEED;
                  break;
          }
      }
  }
    
    checkCollisions();
}

void TankGame::render()
{
  console->fillScreen(console->Color(BLACK));

  for(int i = 0;i<WALL_AMOUNT;i++)
  {
    walls[i].render(console);
  }

  for(int i = 0;i<NUM_TANKS;i++)
  {
    tanks[i].render(console);
  }
}

void TankGame::quit()
{
	
}

void TankGame::menu_init()
{

}

void TankGame::menu_update()
{

}

void TankGame::menu_render()
{

}

void TankGame::menu_quit()
{
  
}

void TankGame::checkCollisions(Tank& t1,Tank& t2)
{
  if(t1.collides(t2))
  {
      if(t1.direction == DOWN)
      {
          if(t1.position.y < t2.position.y)
          {
              t1.position.y-=TANK_SPEED;
          }
          else
          {
              t1.position.y+=TANK_SPEED;
          }
      }
      else if(t1.direction == LEFT)
      {
          if(t1.position.x < t2.position.x)
          {
              t1.position.x-=TANK_SPEED;
          }
          else
          {
              t1.position.x+=TANK_SPEED;
          }
      }
      else if(t1.direction == UP)
      {
          if(t1.position.y < t2.position.y)
          {
              t1.position.y-=TANK_SPEED;
          }
          else
          {
              t1.position.y+=TANK_SPEED;
          }
      }
      else if(t1.direction == RIGHT)
      {
          if(t1.position.x < t2.position.x)
          {
              t1.position.x-=TANK_SPEED;
          }
          else
          {
              t1.position.x+=TANK_SPEED;
          }
      }
  }
}
void TankGame::checkCollisions(Tank& t,Wall& w)
{
  if(t.collides(w))
  {
      if(t.direction == DOWN)
      {
          if(t.position.y < w.position.y)
          {
              t.position.y-=TANK_SPEED;
          }
          else
          {
              t.position.y+=TANK_SPEED;
          }
      }
      else if(t.direction == LEFT)
      {
          if(t.position.x < w.position.x)
          {
              t.position.x-=TANK_SPEED;
          }
          else
          {
              t.position.x+=TANK_SPEED;
          }
      }
      else if(t.direction == UP)
      {
          if(t.position.y < w.position.y)
          {
              t.position.y-=TANK_SPEED;
          }
          else
          {
              t.position.y+=TANK_SPEED;
          }
      }
      else if(t.direction == RIGHT)
      {
          if(t.position.x < w.position.x)
          {
              t.position.x-=TANK_SPEED;
          }
          else
          {
              t.position.x+=TANK_SPEED;
          }
      }
  }
}
void TankGame::checkCollisions()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      for(int j = 0;j<WALL_AMOUNT;j++)
      {
          checkCollisions(tanks[i],walls[j]);
      }
      for(int j = i+1;j<NUM_TANKS;j++)
      {
          if(tanks[i].isInRange(tanks[j]))
              checkCollisions(tanks[i],tanks[j]);
      }
  }
}

void Tank::rotate(byte r)
{
    if(r == RIGHT)
    {
        if(direction == DOWN)
        {
            direction = RIGHT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == LEFT)
        {
            direction = DOWN;
            position.x -= 1;
            position.y += 1;
        }
        else if(direction == UP)
        {
            direction = LEFT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == RIGHT)
        {
            direction = UP;
            position.x -= 1;
            position.y += 1;
        }
    }
    else
    {
        if(direction == DOWN)
        {
            direction = LEFT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == LEFT)
        {
            direction = UP;
            position.x -= 1;
            position.y += 1;
        }
        else if(direction == UP)
        {
            direction = RIGHT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == RIGHT)
        {
            direction = DOWN;
            position.x -= 1;
            position.y += 1;
        }
    }
}
void Tank::move(byte m)
{
  if(m == UP)
  {
      if(direction == DOWN)
      {
          position.y+=TANK_SPEED;
      }
      else if(direction == LEFT)
      {
          position.x-=TANK_SPEED;
      }
      else if(direction == UP)
      {
          position.y-=TANK_SPEED;
      }
      else
      {
          position.x+=TANK_SPEED;
      }
  }
  else
  {
      if(direction == DOWN)
      {
          position.y-=TANK_SPEED;
      }
      else if(direction == LEFT)
      {
          position.x+=TANK_SPEED;
      }
      else if(direction == UP)
      {
          position.y+=TANK_SPEED;
      }
      else
      {
          position.x-=TANK_SPEED;
      }
  }
}
void Tank::shoot()
{
  if(direction == DOWN)
  {
      bullet.position.x = position.x + 1;
      bullet.position.y = position.y + 2;
  }
  else if(direction == LEFT)
  {
      bullet.position.x = position.x - 1;
      bullet.position.y = position.y + 1;
  }
  else if(direction == UP)
  {
      bullet.position.x = position.x + 1;
      bullet.position.y = position.y - 1;
  }
  else if(direction == RIGHT)
  {
      bullet.position.x = position.x + 2;
      bullet.position.y = position.y + 1;
  }
  
  bullet.direction = direction;
}

bool Tank::noseCollides(Wall& w)
{
  if(NOSE_X((*this))< w.position.x + w.width && NOSE_X((*this))+1 > w.position.x &&
      NOSE_Y((*this))<w.position.y + w.height && NOSE_Y((*this))+1 > w.position.y)
  {
     return true;
  }
  
  return false;
}
bool Tank::collides(Wall& w)
{
  if((position.x < w.position.x + w.width && position.x + TANK_WIDTH((*this)) > w.position.x &&
          position.y < w.position.y + w.height && position.y + TANK_HEIGHT((*this)) > w.position.y)
      || noseCollides(w))
  {
      return true;
  }
  
  return false;
}
bool Tank::noseCollidesNose(Tank& t)
{
  if(NOSE_X((*this))< NOSE_X(t) + 1 && NOSE_X((*this))+1 > NOSE_X(t) &&
     NOSE_Y((*this))<NOSE_Y(t) + 1 && NOSE_Y((*this))+1 > NOSE_Y(t))
  {
      return true;
  }
  
  return false;
}
bool Tank::noseCollides(Tank& t)
{
  if(NOSE_X((*this))< t.position.x + TANK_WIDTH(t) && NOSE_X((*this))+1 > t.position.x &&
     NOSE_Y((*this))<t.position.y + TANK_HEIGHT(t) && NOSE_Y((*this))+1 > t.position.y)
  {
      return true;
  }
  
  return false;
}
bool Tank::collides(Tank& t)
{
  if((position.x < t.position.x + TANK_WIDTH(t) && position.x + TANK_WIDTH((*this)) > t.position.x &&
          position.y < t.position.y + TANK_HEIGHT(t) && position.y + TANK_HEIGHT((*this)) > t.position.y)
      || noseCollides(t) || t.noseCollides(*this) || noseCollidesNose(t))
  {
      return true;
  }
  
  return false;
}

bool Tank::isInRange(Tank& t)
{
  if((t.position.x-position.x)*(t.position.x-position.x)+(t.position.y-position.y)*(t.position.y-position.y) < 4*TANK_W*TANK_W)
      return true;
  
  return false;
}

void Tank::render(Console* c)
{
  c->fillRect(position.x,position.y,TANK_WIDTH((*this)),TANK_HEIGHT((*this)),c->Color(color));
  c->drawPixel(NOSE_X((*this)),NOSE_Y((*this)),c->Color(CN));

  if(bullet.position.x != NONE)
    bullet.render(c);
}

void Bullet::render(Console* c)
{
  c->drawPixel(position.x,position.y,c->Color(CB));
}

void Wall::render(Console* c)
{
  c->fillRect(position.x,position.y,width,height,c->Color(CW));
}

