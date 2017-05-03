#include "Controller.h"

Controller::Controller()
{
  
}
Controller::~Controller()
{
  
}

void Controller::setPressed(byte data)
{
  m_pressed = data;
}
void Controller::update()
{
  m_previousPressed = m_pressed;
}

bool Controller::isPressed(byte but) const
{
  return !(m_pressed & but);
}

bool Controller::justPressed(byte but) const
{
  return !(m_pressed & but) && (m_previousPressed & but);
}

bool Controller::isConnected() const
{
  return m_pressed & (CONNECT1 | CONNECT2);
}



