#include <SDL.h>

#include "sdlengine.hpp"
#include "game.hpp"
#include "strResources.hpp"

//------------------------------------------------------------------------------
game::game()
{
  _load_textures();

  float x = (SDLEngine::instance().windowWidth() / 2) - (m_block_a.width() / 2);
  float y1 = SDLEngine::instance().windowHeight() * 0.10f;
  float y2 = SDLEngine::instance().windowHeight() * 0.90f;

  m_block_a.set_position(x, y1);
  m_block_b.set_position(x, y2);

  m_ball_a.add_horizontal_block(m_block_a);
  m_ball_a.add_horizontal_block(m_block_b);

  m_ball_b.add_horizontal_block(m_block_a);
  m_ball_b.add_horizontal_block(m_block_b);

  m_block_c.set_vertical();
  m_block_d.set_vertical();

  float y = (SDLEngine::instance().windowHeight() / 2) - (m_block_c.height() / 2);
  float x1 = SDLEngine::instance().windowWidth() * 0.10;
  float x2 = SDLEngine::instance().windowWidth() * 0.90;

  m_block_c.set_position(x1, y);
  m_block_d.set_position(x2, y);

  m_ball_a.add_vertical_block(m_block_c);
  m_ball_a.add_vertical_block(m_block_d);

  m_ball_b.add_vertical_block(m_block_c);
  m_ball_b.add_vertical_block(m_block_d);

  x = ( SDLEngine::instance().windowWidth() / 2 ) - m_ball_a.width() / 2; 
  y = ( SDLEngine::instance().windowHeight() / 2 ) - m_ball_a.height() / 2;
  m_ball_a.set_position(x, y);

  x = (SDLEngine::instance().windowWidth() / 2) - m_ball_a.width() / 2 - m_ball_a.width() * 2;
  y = (SDLEngine::instance().windowHeight() / 2) - m_ball_a.height() / 2;
  m_ball_b.set_position(x, y);

  m_ball_a.add_ball(m_ball_b);
  m_ball_b.add_ball(m_ball_a);
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
    m_ball_a.move();
    m_ball_b.move();

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
    m_block_a.move_left();
    m_block_b.move_right();
  }
  else if (keystates[SDL_SCANCODE_RIGHT])
  {
    m_block_a.move_right();
    m_block_b.move_left();
  }
  else if(keystates[SDL_SCANCODE_UP])
  {
    m_block_c.move_up();
    m_block_d.move_down();
  }
  else if (keystates[SDL_SCANCODE_DOWN])
  {
    m_block_c.move_down();
    m_block_d.move_up();
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
  m_ball_a.draw();
  m_ball_b.draw();

  m_block_a.draw();
  m_block_b.draw();

  m_block_c.draw();
  m_block_d.draw();
}
//------------------------------------------------------------------------------
void game::_draw_pause()
{
  m_ball_a.draw();
  m_ball_b.draw();

  m_block_a.draw();
  m_block_b.draw();

  m_block_c.draw();
  m_block_d.draw();
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
