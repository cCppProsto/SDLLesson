#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <SDL_opengl.h>
#include <GL/glu.h>

#include "sdlengine.hpp"
#include "settings.hpp"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static std::string   g_window_title{ "Lesson 27" };
static SDL_Window   *g_p_window{ nullptr };
static SDL_GLContext g_gl_context;

static int g_window_width{ 800 };
static int g_window_height{ 800 };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void SDLEngine::setGeometry(int aWidth, int aHeight)
{
  g_window_width = aWidth;
  g_window_height = aHeight;
}
//------------------------------------------------------------------------------
SDLEngine &SDLEngine::instance()
{
  static SDLEngine res;
  return res;
}
//------------------------------------------------------------------------------
SDLEngine::SDLEngine()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    m_last_error += SDL_GetError();
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    m_last_error += SDL_GetError();
    return;
  }

  if (!TTF_WasInit())
  {
    if (TTF_Init() < 0)
    {
      m_last_error += TTF_GetError();
      return;
    }
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    m_last_error += IMG_GetError();
    return;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    m_last_error += Mix_GetError();
    return;
  }

  if (!_load_menu_audio())
    return;

  if (!_load_background_music())
    return;

  // LOAD ALL SETTINGS
  settings::instance();
  g_window_width = settings::instance().screenWidth();
  g_window_height = settings::instance().screenHeight();

  m_is_inited = true;
}
//------------------------------------------------------------------------------
bool SDLEngine::_load_menu_audio()
{
  mp_sound_menu_game_start = Mix_LoadWAV("resources/sounds/menu/item_change.wav");
  if (!mp_sound_menu_game_start)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  mp_sound_menu_item_change = Mix_LoadWAV("resources/sounds/menu/item_change.wav");
  if (!mp_sound_menu_item_change)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  mp_sound_menu_item_enter = Mix_LoadWAV("resources/sounds/menu/item_change.wav");
  if (!mp_sound_menu_item_enter)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  mp_sound_menu_leave = Mix_LoadWAV("resources/sounds/menu/item_change.wav");
  if (!mp_sound_menu_leave)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  mp_sound_menu_change_audio_leave = Mix_LoadWAV("resources/sounds/menu/settings_change_sound_level.wav");
  if (!mp_sound_menu_change_audio_leave)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  return true;
}
//------------------------------------------------------------------------------
bool SDLEngine::_load_background_music()
{
  mp_music_menu_background = Mix_LoadMUS("resources/sounds/menu/background_1.wav");
  if (!mp_music_menu_background)
  {
    m_last_error = Mix_GetError();
    return false;
  }

  return true;
}
//------------------------------------------------------------------------------
SDLEngine::~SDLEngine()
{
  SDL_DestroyWindow(g_p_window);

  _free_audio_menu();
  _free_game_sound_effect();
  _free_background_music();

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  m_is_inited = false;
}
//------------------------------------------------------------------------------
void SDLEngine::_free_audio_menu()
{
  Mix_FreeChunk(mp_sound_menu_game_start);
  Mix_FreeChunk(mp_sound_menu_item_change);
  Mix_FreeChunk(mp_sound_menu_item_enter);
  Mix_FreeChunk(mp_sound_menu_leave);
  Mix_FreeChunk(mp_sound_menu_change_audio_leave);

  mp_sound_menu_game_start = nullptr;
  mp_sound_menu_item_change = nullptr;
  mp_sound_menu_item_enter = nullptr;
  mp_sound_menu_leave = nullptr;
  mp_sound_menu_change_audio_leave = nullptr;
}
//------------------------------------------------------------------------------
void SDLEngine::_free_background_music()
{
  Mix_FreeMusic(mp_music_menu_background);
  mp_music_menu_background = nullptr;
}
//------------------------------------------------------------------------------
void SDLEngine::_free_game_sound_effect()
{
  Mix_FreeChunk(mp_sound_ball_block_collision);
  mp_sound_ball_block_collision = nullptr;
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_game_start() const
{
  Mix_PlayChannel(-1, mp_sound_menu_game_start, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_item_change() const
{
  Mix_PlayChannel(-1, mp_sound_menu_item_change, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_item_enter()const
{
  Mix_PlayChannel(-1, mp_sound_menu_item_enter, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_leave()const
{
  Mix_PlayChannel(-1, mp_sound_menu_leave, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_settings_change_audio_level()const
{
  Mix_PlayChannel(-1, mp_sound_menu_change_audio_leave, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::play_game_ball_block_collision()const
{
  Mix_PlayChannel(-1, mp_sound_ball_block_collision, 0);
}
//------------------------------------------------------------------------------
void SDLEngine::createWindow()
{
  g_p_window = SDL_CreateWindow(g_window_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                g_window_width,
                                g_window_height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (g_p_window == nullptr)
  {
    m_last_error += SDL_GetError();
    return;
  }

  g_gl_context = SDL_GL_CreateContext(g_p_window);
  if (g_gl_context == nullptr)
  {
    m_last_error += SDL_GetError();
    return;
  }

  //SDL_SetWindowFullscreen(g_p_window, SDL_WINDOW_FULLSCREEN);
  SDL_GL_SetSwapInterval(1);

  _gl_init();
}
//------------------------------------------------------------------------------
bool SDLEngine::_gl_init()
{
  GLenum error = GL_NO_ERROR;

  glViewport(0.f, 0.f, g_window_width, g_window_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, g_window_width, g_window_height, 0.0, 1.0, -1.0);

  //Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  error = glGetError();
  if (error != GL_NO_ERROR)
  {
    m_last_error = "Error initializing OpenGL! ";
    m_last_error += (char*)gluErrorString(error);
    return false;
  }

  return true;
}
//------------------------------------------------------------------------------
const bool &SDLEngine::vsync_is_enabled()const
{
  return m_vsynk_is_available;
}
//------------------------------------------------------------------------------
const uint32_t &SDLEngine::screen_fps()const
{
  return m_screen_fps;
}
//------------------------------------------------------------------------------
const uint32_t &SDLEngine::screen_tick_per_fps()const
{
  return m_screen_tick_per_fps;
}
//------------------------------------------------------------------------------
SDL_Window *SDLEngine::window()
{
  return g_p_window;
}
//------------------------------------------------------------------------------
const bool &SDLEngine::isInited()const
{
  return m_is_inited;
}
//------------------------------------------------------------------------------
const int &SDLEngine::windowWidth()const
{
  return g_window_width;
}
//------------------------------------------------------------------------------
const int &SDLEngine::windowHeight()const
{
  return g_window_height;
}
//------------------------------------------------------------------------------
void SDLEngine::setAudioVolume(settings::eAudioLevel aVolume)
{
  Mix_Volume(-1, settings::instance().audioLevelToInt(aVolume));
  Mix_VolumeMusic(settings::instance().audioLevelToInt(aVolume));
}
//------------------------------------------------------------------------------
void SDLEngine::play_menu_background_music()const
{
  if (Mix_PlayingMusic() == 0)
    Mix_PlayMusic(mp_music_menu_background, -1);
  else if (Mix_PausedMusic() == 1)
  {
    Mix_ResumeMusic();
  }
}
//------------------------------------------------------------------------------
void SDLEngine::pause_menu_background_music()const
{
  if (Mix_PlayingMusic() == 1)
  {
    Mix_PauseMusic();
  }
}
//------------------------------------------------------------------------------
void SDLEngine::stop_menu_background_music()const
{
  if (Mix_PlayingMusic() == 1)
  {
    Mix_HaltMusic();
  }
}



