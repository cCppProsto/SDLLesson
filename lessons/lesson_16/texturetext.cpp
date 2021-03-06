#include "texturetext.hpp"

texturetext::texturetext()
{
}
//------------------------------------------------------------------------------
void texturetext::setRenderer(SDL_Renderer *apRenderer)
{
  mp_renderer = apRenderer;
}
//------------------------------------------------------------------------------
bool texturetext::loadFont( std::string path, int size)
{
  free();

  mp_font = TTF_OpenFont(path.c_str(), size);
  if( mp_font == nullptr )
  {
    printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  return mp_font != nullptr;
}
//------------------------------------------------------------------------------
void texturetext::free()
{
  if(mp_font != nullptr)
    TTF_CloseFont( mp_font );
  mp_font = nullptr;

  if( mp_texture != nullptr )
  {
    SDL_DestroyTexture( mp_texture );
    mp_texture = nullptr;
    mWidth = 0;
    mHeight = 0;
  }
}
//------------------------------------------------------------------------------
void texturetext::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  m_color.r = red;
  m_color.g = green;
  m_color.b = blue;
}
//------------------------------------------------------------------------------
void texturetext::setText(std::string text)
{
  m_text = text;

  SDL_Surface* textSurface = TTF_RenderText_Solid( mp_font, m_text.c_str(), m_color );
  if(textSurface != nullptr)
  {
    mp_texture = SDL_CreateTextureFromSurface( mp_renderer, textSurface );
    if(mp_texture != nullptr)
    {
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }
    SDL_FreeSurface( textSurface );
  }
}
//------------------------------------------------------------------------------
void texturetext::setAlpha(Uint8 alpha)
{
  SDL_SetTextureAlphaMod( mp_texture, alpha );
}
//------------------------------------------------------------------------------
void texturetext::render( int x, int y,
                          SDL_Rect* clip,
                          double angle,
                          SDL_Point* center,
                          SDL_RendererFlip flip)
{
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  if( clip != nullptr )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx( mp_renderer, mp_texture, clip, &renderQuad, angle, center, flip );
}
