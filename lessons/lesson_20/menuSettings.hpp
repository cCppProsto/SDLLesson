#ifndef _MENU_SETTINGS_HPP_
#define _MENU_SETTINGS_HPP_

#include <vector>
#include <SDL_events.h>

#include "texturetext.hpp"

class menuSettings
{
  enum class eItem : Uint8
  {
    VideoResolution,
    AudioLevel
  };

  friend menuSettings::eItem operator++(menuSettings::eItem &item);
  friend menuSettings::eItem operator--(menuSettings::eItem &item);

public:
  menuSettings();
  ~menuSettings();

  void draw();
  void process();
  void handle_keyboard_event(const SDL_KeyboardEvent &aEvent);

  void init();
  const bool &isActive()const;

private:
  void _init();
  void _init_resolution_items();
  void _init_audio_level_items();

  void _update_resolution_items();
  void _update_audio_level_items();

  void _unselect_current_item();
  void _select_current_item();

  void _right_keyboard_key_handle();
  void _left_keyboard_key_handle();

  void _uselect_audio_level_values();
  void _update_audio_level_select();

  void _uselect_resolution_values();
  void _update_resolution_select();

private:
  bool m_is_active{ false };

  Uint8 m_alpha_selected{ 255 };
  Uint8 m_alpha_unselected{ 80 };

  eItem m_current_item{ eItem::VideoResolution };

  std::vector<TextureText> mv_items;
  std::vector<TextureText> mv_resolutions_items;
  std::vector<TextureText> mv_audio_levels_items;

  TextureText *mp_resolution_item{ nullptr };
  TextureText *mp_audio_level_item{ nullptr };
};

#endif /* _MENU_SETTINGS_HPP_ */
