#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstddef>
#include <SDL_events.h>

#include "texturetext.hpp"
#include "texture.hpp"
#include "timer.hpp"
#include "firestream.hpp"

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
  void _keyboard_state_process_in_game();

  void _draw_game();
  void _draw_pause();

private:
  bool m_is_run{ false };
  bool m_is_exit{ false };
  bool m_is_pause{ false };

  texture    m_texture;
  firestream m_fire_stream;
};

#endif /* _GAME_HPP_ */
