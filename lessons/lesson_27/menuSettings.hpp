#ifndef _MENU_SETTINGS_HPP_
#define _MENU_SETTINGS_HPP_

#include <vector>
#include <string>
#include <SDL_events.h>

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

  void _right_keyboard_key_handle();
  void _left_keyboard_key_handle();

private:
  bool m_is_active{ false };

  eItem m_current_item{ eItem::VideoResolution };

  std::vector<std::string> mv_items;
  std::vector<std::string> mv_resolutions_items;
  std::vector<std::string> mv_audio_levels_items;
};

#endif /* _MENU_SETTINGS_HPP_ */
