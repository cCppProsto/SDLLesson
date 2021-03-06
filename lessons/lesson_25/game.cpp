#include <SDL.h>

#include "sdlengine.hpp"
#include "game.hpp"
#include "strResources.hpp"

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
  m_bitmap_font.load("resources/fonts/lazyfont.png");
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
  m_bitmap_font.render_text(0, 0, "Bitmap Font:\nABDCEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789");
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
