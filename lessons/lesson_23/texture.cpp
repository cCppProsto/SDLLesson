#include <SDL_image.h>

#include "sdlengine.hpp"
#include "texture.hpp"

texture::texture()
{
}
//------------------------------------------------------------------------------
texture::~texture()
{
  _free();
}
//------------------------------------------------------------------------------
bool texture::load(const std::string &aPath)
{
  _free();

  SDL_Texture* newTexture = nullptr;
  SDL_Surface* loadedSurface = IMG_Load(aPath.c_str());

  if (loadedSurface == nullptr)
    return false;

  newTexture = SDL_CreateTextureFromSurface(SDLEngine::instance().renderer(), loadedSurface);
  if (newTexture == nullptr)
    return false;

  m_width = loadedSurface->w;
  m_height = loadedSurface->h;
  SDL_FreeSurface(loadedSurface);

  m_texture = newTexture;
  return m_texture != nullptr;
}
//------------------------------------------------------------------------------
void texture::setPosition(int aX, int aY)
{
  m_x = aX;
  m_y = aY;
}
//------------------------------------------------------------------------------
void texture::set_alpha(uint8_t aAlpha)
{
  SDL_SetTextureAlphaMod(m_texture, aAlpha);
}
//------------------------------------------------------------------------------
void texture::draw()
{
  SDL_Rect renderQuad = { m_x, m_y, m_width, m_height };
  SDL_RenderCopy(SDLEngine::instance().renderer(), m_texture, nullptr, &renderQuad);
}
//------------------------------------------------------------------------------
void texture::_free()
{
  if (m_texture != nullptr)
  {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}
//------------------------------------------------------------------------------
const int &texture::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const int &texture::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
