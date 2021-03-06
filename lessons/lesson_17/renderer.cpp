#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "renderer.hpp"

//------------------------------------------------------------------------------
SDL_Window   *renderer::mp_window = nullptr;
SDL_Renderer *renderer::mp_renderer = nullptr;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
renderer::renderer(size_t aWidth, size_t aHeight, std::string aTitle)
  :m_width{aWidth}
  ,m_height{aHeight}
  ,m_window_title{aTitle}
{
}
//------------------------------------------------------------------------------
renderer::~renderer()
{
  SDL_DestroyRenderer(mp_renderer);
  SDL_DestroyWindow(mp_window);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  m_is_inited = false;
}
//------------------------------------------------------------------------------
bool renderer::init()
{
  if (mp_window != nullptr)
  {
    m_str_last_error = "Warning: window already created";
    return false;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    return m_is_inited;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    m_str_last_error = "Warning: Linear texture filtering not enabled!";
  }

  mp_window = SDL_CreateWindow(m_window_title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               m_width,
                               m_height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (mp_window == nullptr)
  {
    m_str_last_error = "Window could not be created! SDL_Error:";
    m_str_last_error += SDL_GetError();
    return m_is_inited;
  }

  mp_renderer = SDL_CreateRenderer(mp_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mp_renderer == nullptr)
  {
    m_str_last_error = "Renderer could not be created! SDL Error:";
    m_str_last_error += SDL_GetError();
    return m_is_inited;
  }

  if (!TTF_WasInit())
  {
    if (TTF_Init() < 0)
    {
      m_str_last_error = "SDL_ttf could not initialize! SDL_ttf Error:";
      m_str_last_error += SDL_GetError();
      return m_is_inited;
    }
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    m_str_last_error = "SDL_image could not initialize! SDL_image Error:";
    m_str_last_error += SDL_GetError();
    return m_is_inited;
  }

  _init_objects();

  m_is_inited = true;
  return m_is_inited;
}
//------------------------------------------------------------------------------
void renderer::_init_objects()
{
  m_goblin.loadTexture();
  m_goblin.setDirection(goblinSurface::eDirection::Up_Right);
  
  m_goblin.setPosition(m_width / 2 - m_goblin.width()/2, m_height / 2 - m_goblin.height() / 2);
}
//------------------------------------------------------------------------------
void renderer::run()
{
  m_is_exit = false;

  while (!m_is_exit)
  {
    _event_handle();
    if (m_is_exit)
      continue;

    _process();

    _draw();
  }
}
//------------------------------------------------------------------------------
void renderer::setBackgroundColor(uint8_t aR, uint8_t aG, uint8_t aB)
{
  m_background_r = aR;
  m_background_g = aG;
  m_background_b = aB;
}
//------------------------------------------------------------------------------
void renderer::_event_handle()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      m_is_exit = true;
    }

    m_goblin.handleEvent(e);

    switch (e.type)
    {
      case SDL_MOUSEMOTION:
      {
        int x, y;
        SDL_GetMouseState(&x, &y);
        double radians = atan2(y - m_goblin.y_center(), x - m_goblin.x_center());
        double degree = radians * (180.0 / 3.141592653589793238463);

        if (degree >= -180. && degree <= -90.)
        {
          degree = 270. + (180 - (degree * -1.));
        }
        else
        {
          degree += 90.;
        }

        {
          using dir = goblinSurface::eDirection;
          if (degree >= 337.5 || degree <= 22.5)
          {
            m_goblin.setDirection(dir::Up);
          }
          else if(degree > 22.5 && degree <= 67.5)
          {
            m_goblin.setDirection(dir::Up_Right);
          }
          else if (degree > 67.5 && degree <= 112.5)
          {
            m_goblin.setDirection(dir::Right);
          }
          else if (degree > 112.5 && degree <= 157.5)
          {
            m_goblin.setDirection(dir::Right_Down);
          }
          else if (degree > 157.5 && degree <= 202.5)
          {
            m_goblin.setDirection(dir::Down);
          }
          else if (degree > 202.5 && degree <= 247.5)
          {
            m_goblin.setDirection(dir::Down_Left);
          }
          else if (degree > 247.5 && degree <= 292.5)
          {
            m_goblin.setDirection(dir::Left);
          }
          else if (degree > 292.5 && degree <= 337.5)
          {
            m_goblin.setDirection(dir::Left_Up);
          }
        }
        break;
      }
    }
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    { 
      m_goblin.attack();
    }
  }
}
//------------------------------------------------------------------------------
void renderer::_process()
{
  m_goblin.process();
}
//------------------------------------------------------------------------------
void renderer::_draw()
{
  //Clear screen
  SDL_SetRenderDrawColor(mp_renderer, m_background_r, m_background_g, m_background_b, 0xFF);
  SDL_RenderClear(mp_renderer);

  // draw all objects
  m_goblin.draw();

  //Update screen
  SDL_RenderPresent(mp_renderer);
}
//------------------------------------------------------------------------------
SDL_Renderer *renderer::sdl_renderer()
{
  return mp_renderer;
}

