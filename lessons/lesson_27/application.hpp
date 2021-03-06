#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SDL_events.h>

#include "menu.hpp"
#include "game.hpp"
#include "timer.hpp"
//#include "texturetext.hpp"

class application
{
  enum class eApplicationState
  {
    Menu = 0,
    Main
  };

public:
  static application &instace();

  void run();

private:
  application();
  ~application();

  void _init_sdl_from_settings();
  void _load_textures();

  void _handle_events();
  void _process();
  void _draw();

  void _handle_keyboard_event(const SDL_KeyboardEvent &aEvent);
  void _handle_keyboard_event_menu(const SDL_KeyboardEvent &aEvent);
  void _handle_keyboard_event_main(const SDL_KeyboardEvent &aEvent);

  int _fps_calc();

private:
  bool m_is_run{true};
  
  eApplicationState m_state{ eApplicationState::Menu };

  menu m_menu;
  game m_game;

  uint32_t m_counted_frames{0};
  timer    m_fps_timer;
};

#endif /* _APPLICATION_HPP_ */
