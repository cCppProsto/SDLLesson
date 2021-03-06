#include <SDL.h>
#include <GL/glew.h>
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
      break;
    }
    case eApplicationState::Main:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
void application::_draw()
{
  const auto &id = SDLEngine::instance().gl_program_id();
  const auto &pos = SDLEngine::instance().gl_vertex_pos_2D_location();
  const auto &vbo = SDLEngine::instance().gl_vbo();
  const auto &ibo = SDLEngine::instance().gl_ibo();

  //Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  //Bind program
  glUseProgram(id);

  //Enable vertex position
  glEnableVertexAttribArray(pos);

  //Set vertex data
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
  //Set index data and render
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

  //Disable vertex position
  glDisableVertexAttribArray(pos);

  //Unbind program
  glUseProgram(NULL);

  SDL_GL_SwapWindow(SDLEngine::instance().window());
}
//------------------------------------------------------------------------------
void application::_handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  switch (m_state)
  {
    case eApplicationState::Menu:
    {
      break;
    }
    case eApplicationState::Main:
    {
      break;
    }
  }
}




