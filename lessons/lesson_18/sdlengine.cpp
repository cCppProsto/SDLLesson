#include <SDL_ttf.h>
#include <SDL_image.h>

#include "sdlengine.hpp"

//------------------------------------------------------------------------------
static std::string   g_window_title{ "Lesson 18" };
static SDL_Window   *g_p_window{ nullptr };
static SDL_Renderer *g_p_renderer{ nullptr };

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
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    m_last_error += SDL_GetError();
    return;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    m_last_error += SDL_GetError();
    return;
  }

  if (!TTF_WasInit())
  {
    if (TTF_Init() < 0)
    {
      m_last_error += SDL_GetError();
      return;
    }
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    m_last_error += SDL_GetError();
    return;
  }

  m_is_inited = true;
}
//------------------------------------------------------------------------------
SDLEngine::~SDLEngine()
{
  SDL_DestroyRenderer(g_p_renderer);
  SDL_DestroyWindow(g_p_window);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  m_is_inited = false;
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

  g_p_renderer = SDL_CreateRenderer(g_p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (g_p_renderer == nullptr)
  {
    m_last_error += SDL_GetError();
    return;
  }
}
//------------------------------------------------------------------------------
SDL_Renderer *SDLEngine::renderer()
{
  return g_p_renderer;
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


