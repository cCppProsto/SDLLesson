#ifndef _SDLENGINE_HPP_
#define _SDLENGINE_HPP_

#include <cstddef>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include "settings.hpp"

class SDLEngine
{
public:
  static void setGeometry(int aWidth, int aHeight);
  static SDLEngine &instance();
  void createWindow();

  SDL_Renderer *renderer();

  const bool &isInited()const;
  
  const int &windowWidth()const;
  const int &windowHeight()const;

  void play_menu_game_start()const;
  void play_menu_item_change()const;
  void play_menu_item_enter()const;
  void play_menu_leave()const;
  void play_menu_settings_change_audio_level()const;
  
  void play_menu_background_music()const;
  void pause_menu_background_music()const;
  void stop_menu_background_music()const;

  void setAudioVolume(settings::eAudioLevel aVolume);

  const bool &vsync_is_enabled()const;

  const uint32_t &screen_fps()const;
  const uint32_t &screen_tick_per_fps()const;

private:
  SDLEngine();
  ~SDLEngine();

  void _free_audio_menu();
  bool _load_menu_audio();

private:
  bool m_is_inited{ false };
  bool m_vsynk_is_available{ false };

  const uint32_t m_screen_fps{ 60 };
  const uint32_t m_screen_tick_per_fps{ 1000 / m_screen_fps };

  std::string m_last_error;

  Mix_Chunk *mp_sound_menu_game_start{ nullptr };
  Mix_Chunk *mp_sound_menu_item_change{ nullptr };
  Mix_Chunk *mp_sound_menu_item_enter{ nullptr };
  Mix_Chunk *mp_sound_menu_leave{ nullptr };
  Mix_Chunk *mp_sound_menu_change_audio_leave{ nullptr };
  Mix_Chunk *mp_sound_menu_background{ nullptr };
  Mix_Music *mp_music_menu_background{ nullptr };
};

#endif // _SDLENGINE_HPP_
