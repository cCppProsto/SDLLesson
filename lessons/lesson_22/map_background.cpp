#include <SDL_image.h>

#include "sdlengine.hpp"

#include "map_background.hpp"

static const char * s_texture_path{ "resources/map/mario_map.png" };

//------------------------------------------------------------------------------
map_background::map_background()
{
  _load_texture();
}
//------------------------------------------------------------------------------
map_background::~map_background()
{
  _free();
}
//------------------------------------------------------------------------------
void map_background::draw(const SDL_Rect *aCamera) const
{
  SDL_Rect renderQuad = { 0, SDLEngine::instance().windowHeight() / 2 - m_original_height / 2, aCamera->w, aCamera->h };

  SDL_RenderCopyEx(SDLEngine::instance().renderer(), mp_texture, aCamera, &renderQuad, 0., nullptr, SDL_FLIP_NONE);
}
//------------------------------------------------------------------------------
const float &map_background::width()const
{
  return m_original_width;
}
//------------------------------------------------------------------------------
const float &map_background::height()const
{
  return m_original_height;
}
//------------------------------------------------------------------------------
void map_background::_free()
{
  if (mp_texture != nullptr)
  {
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
    m_original_width = 0;
    m_original_height = 0;
  }
}
//------------------------------------------------------------------------------
void map_background::_load_texture()
{
  _free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(s_texture_path);
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

  mp_texture = newTexture;
}
