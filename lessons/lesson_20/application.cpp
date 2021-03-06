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
  
  _load_textures();

  const bool is_vsynk{ SDLEngine::instance().vsync_is_enabled() };

  m_counted_frames = 0;
  m_fps_timer.start();

  timer cap_timer;
  while (m_is_run)
  {
    if (!is_vsynk)
    {
      cap_timer.reset();
      cap_timer.start();
    }

    m_fps_texture.setText(std::to_string(_fps_calc()));

    _handle_events();

    _process();

    _draw();

    ++m_counted_frames;
    if (!is_vsynk)
    {
      static const auto &tick_per_frame{ SDLEngine::instance().screen_tick_per_fps() };
      if (cap_timer.ticks() < tick_per_frame)
        SDL_Delay(tick_per_frame - cap_timer.ticks());
    }
  }
}
//------------------------------------------------------------------------------
int application::_fps_calc()
{
  static float avgFPS{ 0 };
  avgFPS = m_counted_frames / (m_fps_timer.ticks() / 1000.f);
  if (avgFPS > 2000000)
    avgFPS = 0;

  return static_cast<int>(avgFPS);
}
//------------------------------------------------------------------------------
void application::_init_sdl_from_settings()
{
  SDLEngine::instance().setAudioVolume(settings::instance().audioLevel());

  SDLEngine::instance().play_menu_background_music();
}
//------------------------------------------------------------------------------
void application::_load_textures()
{
  m_fps_texture.loadFont("resources/fonts/a_Albionic.ttf", 15);
  m_fps_texture.setColor(255, 255, 125);
  m_fps_texture.setText("10000");
  m_fps_texture.setAlpha(255);
  m_fps_texture.setPos(settings::instance().screenWidth() - m_fps_texture.width(), m_fps_texture.height());
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

  m_fps_texture.render();

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



