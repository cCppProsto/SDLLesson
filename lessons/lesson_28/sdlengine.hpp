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

  SDL_Window   *window();

  const bool &isInited()const;

  const int &windowWidth()const;
  const int &windowHeight()const;

  void play_menu_game_start()const;
  void play_menu_item_change()const;
  void play_menu_item_enter()const;
  void play_menu_leave()const;
  void play_menu_settings_change_audio_level()const;

  void play_game_ball_block_collision()const;

  void play_menu_background_music()const;
  void pause_menu_background_music()const;
  void stop_menu_background_music()const;

  void setAudioVolume(settings::eAudioLevel aVolume);

  const bool &vsync_is_enabled()const;

  const uint32_t &screen_fps()const;
  const uint32_t &screen_tick_per_fps()const;

  const GLuint &gl_program_id()const;
  const GLint &gl_vertex_pos_2D_location()const;
  const GLuint &gl_vbo()const;
  const GLuint &gl_ibo()const;

private:
  SDLEngine();
  ~SDLEngine();

  bool _gl_init();

  bool _load_menu_audio();
  bool _load_background_music();

  void _free_audio_menu();
  void _free_background_music();
  void _free_game_sound_effect();

private:
  bool m_is_inited{ false };
  bool m_vsynk_is_available{ true };

  const uint32_t m_screen_fps{ 30 };
  const uint32_t m_screen_tick_per_fps{ 1000 / m_screen_fps };

  GLuint m_gl_program_id{ 0 };
  GLint m_gl_vertex_pos_2D_location{-1};
  GLuint m_gl_vbo{ 0 };
  GLuint m_gl_ibo{ 0 };
  
  std::string m_last_error;

  Mix_Chunk *mp_sound_menu_game_start{ nullptr };
  Mix_Chunk *mp_sound_menu_item_change{ nullptr };
  Mix_Chunk *mp_sound_menu_item_enter{ nullptr };
  Mix_Chunk *mp_sound_menu_leave{ nullptr };
  Mix_Chunk *mp_sound_menu_change_audio_leave{ nullptr };
  Mix_Chunk *mp_sound_menu_background{ nullptr };
  Mix_Music *mp_music_menu_background{ nullptr };

  Mix_Chunk *mp_sound_ball_block_collision{ nullptr };
};

#endif // _SDLENGINE_HPP_
