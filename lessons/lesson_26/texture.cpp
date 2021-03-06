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

  auto renderer{ SDLEngine::instance().renderer() };
  auto window{ SDLEngine::instance().window() };

  SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
  if (formattedSurface == nullptr)
    return false;

  newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
  if (newTexture == nullptr)
    return false;

  SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

  SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &mp_pixels, &m_pitch);

  memcpy(mp_pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

  m_width = formattedSurface->w ;
  m_height = formattedSurface->h;

  Uint32* pixels = (Uint32*)mp_pixels;
  int pixelCount = (m_pitch / 4) * m_height;

  Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
  Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

  for (int i = 0; i < pixelCount; ++i)
  {
    if (pixels[i] == colorKey)
    {
      pixels[i] = transparent;
    }
    else
    {
      pixels[i] = SDL_MapRGBA(formattedSurface->format, 0xFF, 0x00, 0x00, 0xFF);
    }
  }

  SDL_UnlockTexture(newTexture);
  mp_pixels = nullptr;

  SDL_FreeSurface(formattedSurface);
  SDL_FreeSurface(loadedSurface);

  m_texture = newTexture;

  return m_texture != nullptr;
}
//------------------------------------------------------------------------------
bool texture::lock()
{
  if (mp_pixels != nullptr)
    return false;

  if (SDL_LockTexture(m_texture, nullptr, &mp_pixels, &m_pitch) != 0)
    return false;

  return true;
}
//------------------------------------------------------------------------------
bool texture::unlock()
{
  if (m_texture == nullptr)
    return false;

  SDL_UnlockTexture(m_texture);
  mp_pixels = nullptr;
  m_pitch = 0;

  return true;
}
//------------------------------------------------------------------------------
bool texture::create_blank(int aWidth, int aHeight)
{
  m_texture = SDL_CreateTexture(SDLEngine::instance().renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, aWidth, aHeight);
  if (m_texture == nullptr)
    return false;

  SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);

  m_width = aWidth;
  m_height = aHeight;

  return true;
}
//------------------------------------------------------------------------------
void texture::copy_pixels(void* pixels)
{
  if (m_texture != nullptr)
    memcpy(mp_pixels, pixels, m_pitch * m_height);
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
void texture::draw(int x, int y, SDL_Rect* clip /* = nullptr */ )
{
  SDL_Rect renderQuad = { x, y, m_width, m_height };

  if (clip != nullptr)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(SDLEngine::instance().renderer(), m_texture, clip, &renderQuad, 0, nullptr, SDL_FLIP_NONE);
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
Uint32 texture::get_pixel32(unsigned int x, unsigned int y)
{
  //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32*)mp_pixels;

  //Get the pixel requested
  return pixels[(y * (m_pitch / 4)) + x];
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
