#include <SDL.h>
#include <SDL_opengl.h>

#include "sdlengine.hpp"
#include "game.hpp"

//------------------------------------------------------------------------------
game::game()
{
  _load_textures();
}
//------------------------------------------------------------------------------
game::~game()
{
}
//------------------------------------------------------------------------------
void game::_load_textures()
{
}
//------------------------------------------------------------------------------
void game::draw()
{
  if (m_is_run)
  {
    _draw_game();
  }

  if (m_is_pause)
  {
    _draw_pause();
  }
}
//------------------------------------------------------------------------------
void game::process()
{
  if (m_is_run)
  {
    _keyboard_state_process_in_game();
    return;
  }

  if (m_is_pause)
  {
    return;
  }
}
//------------------------------------------------------------------------------
void game::_keyboard_state_process_in_game()
{
  const Uint8* keystates = SDL_GetKeyboardState(NULL);
  if (keystates[SDL_SCANCODE_LEFT])
  {
    
  }
  else if (keystates[SDL_SCANCODE_RIGHT])
  {
  }
  else if(keystates[SDL_SCANCODE_UP])
  {
  }
  else if (keystates[SDL_SCANCODE_DOWN])
  {
  }
}
//------------------------------------------------------------------------------
void game::handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  if (m_is_run)
  {
    _handle_keyboard_event_run(aEvent);
    return;
  }

  if (m_is_pause)
  {
    _handle_keyboard_event_pause(aEvent);
    return;
  }
}
//------------------------------------------------------------------------------
void game::_handle_keyboard_event_run(const SDL_KeyboardEvent &aEvent)
{
  switch (aEvent.state)
  {
    case SDL_PRESSED:
    {
      switch (aEvent.keysym.sym)
      {
      }
      break;
    }
    case SDL_RELEASED:
    {
      switch (aEvent.keysym.sym)
      {
        case SDLK_ESCAPE:
        {
          m_is_pause = true;
          m_is_run   = false;
          break;
        }
        case SDLK_DOWN:
        {
          break;
        }
        case SDLK_UP:
        {
          break;
        }
        case SDLK_RETURN:
        {
          break;
        }
      }
      break;
    }
  }
}
//------------------------------------------------------------------------------
void game::_handle_keyboard_event_pause(const SDL_KeyboardEvent &aEvent)
{
  switch (aEvent.state)
  {
    case SDL_PRESSED:
    {
      break;
    }
    case SDL_RELEASED:
    {
      switch (aEvent.keysym.sym)
      {
        case SDLK_ESCAPE:
        {
          m_is_pause = false;
          m_is_run = false;
          m_is_exit = true;
          break;
        }
        case SDLK_RETURN:
        {
          m_is_pause = false;
          m_is_run = true;
          m_is_exit = false;
          break;
        }
      }
      break;
    }
  }
}
//------------------------------------------------------------------------------
void game::_draw_game()
{
  glColor3ub(10, 200, 45);
  glBegin(GL_QUADS);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(100, 300);
  glEnd();

  glShadeModel(GL_SMOOTH);    // as opposed to GL_FLAT
  glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);   // red
    glVertex2i(200, 400);
    glColor3ub(0, 255, 0);   // green
    glVertex2i(500, 200);
    glColor3ub(255, 0, 0);   // blue
    glVertex2i(300, 500);
  glEnd();
}
//------------------------------------------------------------------------------
void game::_draw_pause()
{
}
//------------------------------------------------------------------------------
void game::init()
{
  m_is_exit = false;
  m_is_pause = false;
  m_is_run = true;
}
//------------------------------------------------------------------------------
const bool &game::isExit()const
{
  return m_is_exit;
}
