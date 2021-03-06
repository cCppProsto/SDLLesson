#include <SDL_image.h>

#include "sdlengine.hpp"
#include "block.hpp"

static const char * s_horizontal_texture { "resources/pics/block_horizontal_hight_resolution.png" };
static const char * s_vertical_texture   { "resources/pics/block_vertical_hight_resolution.png" };

//------------------------------------------------------------------------------
block::block()
{
  _load_horizontal_texture(s_horizontal_texture);

  m_dx = SDLEngine::instance().windowWidth() / 100;
  m_dy = SDLEngine::instance().windowHeight() / 100;

  // init start Y position
  m_y = SDLEngine::instance().windowHeight() * 0.9;
}
//------------------------------------------------------------------------------
block::~block()
{
}
//------------------------------------------------------------------------------
void block::set_horizontal()
{
  _load_horizontal_texture(s_horizontal_texture);
}
//------------------------------------------------------------------------------
void block::set_vertical()
{
  _load_vertical_texture(s_vertical_texture);
}
//------------------------------------------------------------------------------
void block::set_position(int aX, int aY)
{
  m_x = aX;
  m_y = aY;
}
//------------------------------------------------------------------------------
void block::move_left()
{
  if (m_x >= m_dx)
    m_x -= m_dx;
  else
    m_x = 0;
}
//------------------------------------------------------------------------------
void block::move_right()
{
  const auto &w_w{ SDLEngine::instance().windowWidth() };
  if (m_x + m_width + m_dx <= w_w)
    m_x += m_dx;
  else
    m_x = SDLEngine::instance().windowWidth() - m_width;
}
//------------------------------------------------------------------------------
void block::move_up()
{
  if (m_y >= m_dy)
    m_y -= m_dy;
  else
    m_y = 0;
}
//------------------------------------------------------------------------------
void block::move_down()
{
  const auto &w_h{ SDLEngine::instance().windowHeight() };
  if (m_y + m_height + m_dy <= w_h)
    m_y += m_dy;
  else
    m_y = SDLEngine::instance().windowHeight() - m_height;
}
//------------------------------------------------------------------------------
const float &block::x()const
{
  return m_x;
}
//------------------------------------------------------------------------------
const float &block::y()const
{
  return m_y;
}
//------------------------------------------------------------------------------
const float &block::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const float &block::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
void block::draw()
{
  SDL_Rect renderQuad = { m_x, m_y, static_cast<int>(m_width), static_cast<int>(m_height) };

  SDL_RenderCopy(SDLEngine::instance().renderer(), mp_texture, nullptr, &renderQuad);
}
//------------------------------------------------------------------------------
void block::_load_vertical_texture(const char *aTexturePath)
{
  _free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(aTexturePath);
  if (loadedSurface == nullptr)
  {
  }
  else
  {
    newTexture = SDL_CreateTextureFromSurface(SDLEngine::instance().renderer(), loadedSurface);
    if (newTexture == nullptr)
    {
    }
    else
    {
      m_original_width = static_cast<size_t>(loadedSurface->w);
      m_original_height = static_cast<size_t>(loadedSurface->h);
    }

    SDL_FreeSurface(loadedSurface);
  }

  m_width = SDLEngine::instance().windowWidth() / 100;
  m_height = SDLEngine::instance().windowHeight() / 5;

  mp_texture = newTexture;
}
//------------------------------------------------------------------------------
void block::_load_horizontal_texture(const char *aTexturePath)
{
  _free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(aTexturePath);
  if (loadedSurface == nullptr)
  {
  }
  else
  {
    newTexture = SDL_CreateTextureFromSurface(SDLEngine::instance().renderer(), loadedSurface);
    if (newTexture == nullptr)
    {
    }
    else
    {
      m_original_width = static_cast<size_t>(loadedSurface->w);
      m_original_height = static_cast<size_t>(loadedSurface->h);
    }

    SDL_FreeSurface(loadedSurface);
  }

  m_width = SDLEngine::instance().windowWidth() / 5;
  m_height = SDLEngine::instance().windowHeight() / 100;

  mp_texture = newTexture;
}
//------------------------------------------------------------------------------
void block::_free()
{
  if (mp_texture != nullptr)
  {
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
    m_original_width = 0;
    m_original_height = 0;
  }
}

