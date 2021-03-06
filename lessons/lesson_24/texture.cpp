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

  SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(window), 0);
  if (formattedSurface == nullptr)
    return false;

  newTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
  if (newTexture == nullptr)
    return false;

  int mPitch;
  SDL_LockTexture(newTexture, nullptr, &mp_pixels, &mPitch);
  memcpy(mp_pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);
  SDL_UnlockTexture(newTexture);
  mp_pixels = nullptr;

  m_width = loadedSurface->w;
  m_height = loadedSurface->h;

  SDL_FreeSurface(formattedSurface);
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
void texture::change_pixel_color_a()
{
  auto renderer{ SDLEngine::instance().renderer() };
  auto window{ SDLEngine::instance().window() };

  int mPitch;
  SDL_LockTexture(m_texture, nullptr, &mp_pixels, &mPitch);

  Uint32* pixels = (Uint32*)mp_pixels;
  int pixelCount = (mPitch / 4) * m_height;

  for (int i = 0; i < pixelCount; ++i)
  {
    pixels[i] = pixels[i] / 0.01;
  }

  SDL_UnlockTexture(m_texture);
}
//------------------------------------------------------------------------------
void texture::change_pixel_color_b()
{
  auto window{ SDLEngine::instance().window() };

  int mPitch;
  SDL_LockTexture(m_texture, nullptr, &mp_pixels, &mPitch);

  Uint32 format = SDL_GetWindowPixelFormat(window);
  SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

  Uint32* pixels = (Uint32*)mp_pixels;
  int pixelCount = (mPitch / 4) * m_height;

  Uint8 red, green, blue;
  for (int i = 0; i < pixelCount; ++i)
  {
    SDL_GetRGB(pixels[i], mappingFormat, &red, &green, &blue);
    
    red *= ((rand() % 2) ? 0.9 : 1.1);
    green *= ((rand() % 2) ? 0.9 : 1.1);
    blue *= ((rand() % 2) ? 0.9 : 1.1);

    pixels[i] = SDL_MapRGB(mappingFormat, red, green, blue);
  }

  SDL_UnlockTexture(m_texture);
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
