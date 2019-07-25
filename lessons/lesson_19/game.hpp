#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstddef>
#include <SDL_events.h>

#include "texturetext.hpp"

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

  uint32_t m_start_game_ticks{ 0 };
  uint32_t m_game_ticks{0};
  uint32_t m_game_common_ticks{ 0 };

  uint32_t m_start_pause_ticks{ 0 };
  uint32_t m_pause_ticks{ 0 };
  uint32_t m_pause_common_ticks{ 0 };

  TextureText m_pause_ticks_texture;
  TextureText m_game_ticks_texture;

  TextureText m_game_text_texture;
  TextureText m_pause_text_texture;

  TextureText m_ms_game_text_texture;
  TextureText m_ms_pause_text_texture;
};

#endif /* _GAME_HPP_ */
