#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SDL_events.h>

#include "menu.hpp"

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

  void _handle_events();
  void _process();
  void _draw();

  void _handle_keyboard_event(const SDL_KeyboardEvent &aEvent);
  void _handle_keyboard_event_menu(const SDL_KeyboardEvent &aEvent);
  void _handle_keyboard_event_main(const SDL_KeyboardEvent &aEvent);

private:
  bool m_is_run{true};
  
  eApplicationState m_state{ eApplicationState::Menu };

  uint8_t m_background_r{ 0 };
  uint8_t m_background_g{ 0 };
  uint8_t m_background_b{ 0 };

  menu m_menu;
};

#endif /* _APPLICATION_HPP_ */
