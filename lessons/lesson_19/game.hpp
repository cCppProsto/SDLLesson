#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstddef>
#include <SDL_events.h>

#include "texturetext.hpp"
#include "timer.hpp"

class game
{
public:
  game();
  ~game();

  void draw();
  void process();
  void handle_keyboard_event(const SDL_KeyboardEvent &aEvent);

  void init();

  const bool &isExit()const;

private:

  void _load_textures();

  void _handle_keyboard_event_run(const SDL_KeyboardEvent &aEvent);
  void _handle_keyboard_event_pause(const SDL_KeyboardEvent &aEvent);

  void _draw_game();
  void _draw_pause();

private:
  bool m_is_run{ false };
  bool m_is_exit{ false };
  bool m_is_pause{ false };

  timer m_timer_game;
  timer m_timer_pause;

  TextureText m_pause_ticks_texture;
  TextureText m_game_ticks_texture;

  TextureText m_game_text_texture;
  TextureText m_pause_text_texture;

  TextureText m_ms_game_text_texture;
  TextureText m_ms_pause_text_texture;
};

#endif /* _GAME_HPP_ */
