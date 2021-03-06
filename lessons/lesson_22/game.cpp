#include <SDL.h>

#include "sdlengine.hpp"
#include "game.hpp"
#include "strResources.hpp"


static float g_camera_pos_x = 0.f;

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
    g_camera_pos_x -= 2.5f;
    if(g_camera_pos_x < 0.f)
      g_camera_pos_x = 0.f;
  }
  else if (keystates[SDL_SCANCODE_RIGHT])
  {
    g_camera_pos_x += 2.5f;
    if ((g_camera_pos_x + SDLEngine::instance().windowWidth()) >= m_map.width())
      g_camera_pos_x = m_map.width() - SDLEngine::instance().windowWidth();
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
        case SDLK_UP:
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
  static SDL_Rect camera = { 0, 0, SDLEngine::instance().windowWidth(), m_map.height() };

  camera.x = g_camera_pos_x;

  m_map.draw(&camera);
}
//------------------------------------------------------------------------------
void game::_draw_pause()
{
  SDL_Rect camera = { 0, 0, SDLEngine::instance().windowWidth(), m_map.height() };
  m_map.draw(&camera);
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
