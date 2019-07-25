#include <SDL.h>

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
  m_game_ticks_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_game_ticks_texture.setColor(80, 30, 125);
  m_game_ticks_texture.setText("0");
  m_game_ticks_texture.setAlpha(255);
  m_game_ticks_texture.setPos(200, 100);

  m_game_text_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_game_text_texture.setColor(80, 30, 125);
  m_game_text_texture.setText(strResources::game_text_u8());
  m_game_text_texture.setAlpha(255);
  m_game_text_texture.setPos(0, 40);

  m_ms_game_text_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_ms_game_text_texture.setColor(80, 30, 125);
  m_ms_game_text_texture.setText(strResources::ms_text_u8());
  m_ms_game_text_texture.setAlpha(180);
  m_ms_game_text_texture.setPos(300, 100);


  m_pause_ticks_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_pause_ticks_texture.setColor(125, 30, 80);
  m_pause_ticks_texture.setText("0");
  m_pause_ticks_texture.setAlpha(255);
  m_pause_ticks_texture.setPos(200, 200);

  m_pause_text_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_pause_text_texture.setColor(125, 30, 80);
  m_pause_text_texture.setText(strResources::pause_text_u8());
  m_pause_text_texture.setAlpha(255);
  m_pause_text_texture.setPos(0, 40);

  m_ms_pause_text_texture.loadFont("resources/fonts/a_Albionic.ttf", 32);
  m_ms_pause_text_texture.setColor(125, 30, 80);
  m_ms_pause_text_texture.setText(strResources::ms_text_u8());
  m_ms_pause_text_texture.setAlpha(180);
  m_ms_pause_text_texture.setPos(300, 200);
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

  m_game_ticks_texture.render();
  m_ms_game_text_texture.render();

  m_pause_ticks_texture.render();
  m_ms_pause_text_texture.render();
}
//------------------------------------------------------------------------------
void game::process()
{
  if (m_is_run)
  {
    m_game_ticks = m_game_common_ticks + SDL_GetTicks() - m_start_game_ticks;
    m_game_ticks_texture.setText(std::to_string(m_game_ticks));
    return;
  }

  if (m_is_pause)
  {
    m_pause_ticks = m_pause_common_ticks + SDL_GetTicks() - m_start_pause_ticks;
    m_pause_ticks_texture.setText(std::to_string(m_pause_ticks));
    return;
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
          m_game_common_ticks = m_game_ticks;
          m_game_ticks = 0;

          m_start_pause_ticks = SDL_GetTicks();
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
          m_start_game_ticks = SDL_GetTicks();

          m_pause_common_ticks = m_pause_ticks;
          m_pause_ticks = 0;
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
  m_game_text_texture.render();
}
//------------------------------------------------------------------------------
void game::_draw_pause()
{
  m_pause_text_texture.render();
}
//------------------------------------------------------------------------------
void game::init()
{
  m_is_exit = false;
  m_is_pause = false;
  m_is_run = true;

  m_game_ticks = 0;
  m_game_common_ticks = 0;
  m_start_game_ticks = SDL_GetTicks();

  m_pause_ticks = 0;
  m_pause_common_ticks = 0;
  m_start_pause_ticks = SDL_GetTicks();

  m_game_ticks_texture.setText("0");
  m_pause_ticks_texture.setText("0");
}
//------------------------------------------------------------------------------
const bool &game::isExit()const
{
  return m_is_exit;
}
