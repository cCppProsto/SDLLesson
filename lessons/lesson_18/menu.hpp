#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <vector>
#include <SDL2/SDL_events.h>

#include "texturetext.hpp"
#include "menuSettings.hpp"

class menu
{
  enum class eItem : Uint8
  {
    Start = 0,
    Settings,
    Authors,
    Exit
  };

  friend menu::eItem operator++(menu::eItem &item);
  friend menu::eItem operator--(menu::eItem &item);

public:
  menu();
  ~menu();

  void draw();
  void process();
  void handle_keyboard_event(const SDL_KeyboardEvent &aEvent);

  const bool &isExit()const;

private:
  void _init_text();
  void _load_sound();
  void _change_state();

private:
  Uint8 m_alpha_selected{ 255 };
  Uint8 m_alpha_unselected{ 80 };

  bool m_is_start{ false };
  bool m_is_exit{false};
  bool m_is_high_level{ true };
  eItem m_current_item{ eItem::Start };

  menuSettings m_settings_page;

  std::vector<TextureText> mv_items;
};

#endif /* _MENU_HPP_ */
