#include <GL/glut.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

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
  //Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  std::string fps_str{ "fps: " + std::to_string(_fps_calc()) };
  glColor3ub(255, 255, 255);

  glRasterPos2f(SDLEngine::instance().windowWidth() - 39, 20);
  for (auto c : fps_str)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);

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
  SDL_GL_SwapWindow(SDLEngine::instance().window());
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



