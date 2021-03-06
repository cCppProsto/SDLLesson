#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <SDL.h>
#include <GL/glew.h>
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

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

  //Initialize GLEW
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK)
  {
    m_last_error = "Error initializing GLEW! ";
    m_last_error += (char*)glewGetErrorString(glewError);
    return;
  }

  SDL_GL_SetSwapInterval(1);

  _gl_init();
}
//------------------------------------------------------------------------------
bool SDLEngine::_gl_init()
{
  GLenum error = GL_NO_ERROR;

  m_gl_program_id = glCreateProgram();

  //Create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  //Get vertex source
  const GLchar* vertexShaderSource[] =
  {
    "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
  };

  //Set vertex source
  glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);

  //Compile vertex source
  glCompileShader(vertexShader);

  //Check vertex shader for errors
  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

  if (vShaderCompiled != GL_TRUE)
  {
    m_last_error = "Unable to compile vertex shader";
    return false;
  }

  //Attach vertex shader to program
  glAttachShader(m_gl_program_id, vertexShader);

  //Create fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  //Get fragment source
  const GLchar* fragmentShaderSource[] =
  {
    "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
  };

  //Set fragment source
  glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

  //Compile fragment source
  glCompileShader(fragmentShader);

  //Check fragment shader for errors
  GLint fShaderCompiled = GL_FALSE;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
  if (fShaderCompiled != GL_TRUE)
  {
    m_last_error = "Unable to compile fragment shader";
    return false;
  }

  //Attach fragment shader to program
  glAttachShader(m_gl_program_id, fragmentShader);

  //Link program
  glLinkProgram(m_gl_program_id);

  //Check for errors
  GLint programSuccess = GL_TRUE;
  glGetProgramiv(m_gl_program_id, GL_LINK_STATUS, &programSuccess);
  if (programSuccess != GL_TRUE)
  {
    m_last_error = "Error linking program";
    return false;
  }

  //Get vertex attribute location
  m_gl_vertex_pos_2D_location = glGetAttribLocation(m_gl_program_id, "LVertexPos2D");
  if (m_gl_vertex_pos_2D_location == -1)
  {
    m_last_error = "LVertexPos2D is not a valid glsl program variable!";
    return false;
  }

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //VBO data
  GLfloat vertexData[] =
  {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f,  0.5f,
    -0.5f,  0.5f
  };

  //IBO data
  GLuint indexData[] = { 0, 1, 2, 3 };

  //Create VBO
  glGenBuffers(1, &m_gl_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_gl_vbo);
  glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

  //Create IBO
  glGenBuffers(1, &m_gl_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

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
//------------------------------------------------------------------------------
const GLuint &SDLEngine::gl_program_id()const
{
  return m_gl_program_id;
}
//------------------------------------------------------------------------------
const GLint &SDLEngine::gl_vertex_pos_2D_location()const
{
  return m_gl_vertex_pos_2D_location;
}
//------------------------------------------------------------------------------
const GLuint &SDLEngine::gl_vbo()const
{
  return m_gl_vbo;
}
//------------------------------------------------------------------------------
const GLuint &SDLEngine::gl_ibo()const
{
  return m_gl_ibo;
}



