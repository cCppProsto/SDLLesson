#ifndef _STR_RESOURCES_HPP_
#define _STR_RESOURCES_HPP_

#include <string>

struct strResources
{
  static const std::string &start_u8();
  static const std::string &settings_u8();
  static const std::string &authors_u8();
  static const std::string &exit_u8();

  static const std::string &screen_resolution_u8();
  static const std::string &level_sound_u8();

  static const std::string &pause_text_u8();
  static const std::string &game_text_u8();
  static const std::string &ms_text_u8();
};

#endif /* _STR_RESOURCES_HPP_ */
