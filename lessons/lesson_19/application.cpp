#include "application.hpp"

#include "settings.hpp"
#include "sdlengine.hpp"

//------------------------------------------------------------------------------
application &application::instace()
{
  static application inst;
  return inst;
}
//------------------------------------------------------------------------------
application::application()
{
}
//------------------------------------------------------------------------------
application::~application()
{
}
//------------------------------------------------------------------------------
void application::run()
{
  m_is_run = true;
  if (!SDLEngine::instance().isInited())
    m_is_run = false;

  _init_sdl_from_settings();

  while (m_is_run)
  {
    _handle_events();

    _process();

    _draw();
  }
}
//------------------------------------------------------------------------------
void application::_init_sdl_from_settings()
{
  SDLEngine::instance().setAudioVolume(settings::instance().audioLevel());
}
//------------------------------------------------------------------------------
void application::_handle_events()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0)
  {
    switch (e.type)
    {
      case SDL_QUIT:
      {
        m_is_run = false;
        break;
      }
      case SDL_KEYDOWN:
      case SDL_KEYUP:
      {
        _handle_keyboard_event(e.key);
        break;
      }
    }
  }
}
//------------------------------------------------------------------------------
void application::_process()
{
  // draw all objects
  switch (m_state)
  {
    case eApplicationState::Menu:
    {
      m_menu.process();
      break;
    }
    case eApplicationState::Main:
    {
      m_game.process();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void application::_draw()
{
  static auto renderer{ SDLEngine::instance().renderer() };
  SDL_SetRenderDrawColor(renderer, m_background_r, m_background_g, m_background_b, 0xFF);
  SDL_RenderClear(renderer);

  // draw all objects
  switch (m_state)
  {
    case eApplicationState::Menu:
    {
      m_menu.draw();
      break;
    }
    case eApplicationState::Main:
    {
      m_game.draw();
      break;
    }
  }


  //Update screen
  SDL_RenderPresent(renderer);
}
//------------------------------------------------------------------------------
void application::_handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  switch (m_state)
  {
    case eApplicationState::Menu:
    {
      _handle_keyboard_event_menu(aEvent);
      break;
    }
    case eApplicationState::Main:
    {
      _handle_keyboard_event_main(aEvent);
      break;
    }
  }
}
//------------------------------------------------------------------------------
void application::_handle_keyboard_event_menu(const SDL_KeyboardEvent &aEvent)
{
  m_menu.handle_keyboard_event(aEvent);

  if (m_menu.isExit())
  {
    m_is_run = false;
  }
  else if (m_menu.isGameStart())
  {
    m_menu.reset_flags();
    m_game.init();
    m_state = eApplicationState::Main;
  }
}
//------------------------------------------------------------------------------
void application::_handle_keyboard_event_main(const SDL_KeyboardEvent &aEvent)
{
  m_game.handle_keyboard_event(aEvent);

  if (m_game.isExit())
  {
    m_state = eApplicationState::Menu;
  }
}



