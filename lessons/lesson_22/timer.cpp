#include <SDL.h>

#include "timer.hpp"


timer::timer()
{
}
timer::~timer()
{
}
//------------------------------------------------------------------------------
void timer::start()
{
  if (m_is_started && m_is_paused)
  {
    m_is_paused = false;
    m_start_ticks = SDL_GetTicks() - m_paused_ticks;
    m_paused_ticks = 0;
  }
  else
  {
    m_is_started = true;
    m_is_paused = false;

    m_start_ticks = SDL_GetTicks();
    m_paused_ticks = 0;
  }
}
//------------------------------------------------------------------------------
void timer::stop()
{
  m_is_started = false;
  m_is_paused = false;

  m_start_ticks = 0;
  m_paused_ticks = 0;
}
//------------------------------------------------------------------------------
void timer::pause()
{
  if (m_is_started && !m_is_paused)
  {
    m_is_paused = true;

    m_paused_ticks = SDL_GetTicks() - m_start_ticks;
    m_start_ticks = 0;
  }
}
//------------------------------------------------------------------------------
void timer::reset()
{
  m_is_started = false;
  m_is_paused = false;
  m_start_ticks = 0;
  m_paused_ticks = 0;
}
//------------------------------------------------------------------------------
const bool &timer::is_paused()const
{
  return m_is_paused;
}
//------------------------------------------------------------------------------
const bool &timer::is_started()const
{
  return m_is_started;
}
//------------------------------------------------------------------------------
uint32_t timer::ticks()const
{
  uint32_t time = 0;

  if (m_is_started)
  {
    if (m_is_paused)
    {
      time = m_paused_ticks;
    }
    else
    {
      time = SDL_GetTicks() - m_start_ticks;
    }
  }
  return time;
}
