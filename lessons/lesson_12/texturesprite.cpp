#include "texturesprite.hpp"

#include <SDL2/SDL_image.h>

//------------------------------------------------------------------------------
TextureSprite::TextureSprite()
{

}
//------------------------------------------------------------------------------
TextureSprite::~TextureSprite()
{
  free();
}
//------------------------------------------------------------------------------
void TextureSprite::setRenderer(SDL_Renderer *apRenderer)
{
  mpRenderer = apRenderer;
}
//------------------------------------------------------------------------------
bool TextureSprite::loadFromFile( std::string path)
{
  free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == nullptr )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  }
  else
  {
    newTexture = SDL_CreateTextureFromSurface( mpRenderer, loadedSurface );
    if( newTexture == nullptr )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
      mWidth = static_cast<size_t>(loadedSurface->w);
      mHeight = static_cast<size_t>(loadedSurface->h);
    }

    SDL_FreeSurface( loadedSurface );
  }

  mTexture = newTexture;
  return mTexture != nullptr;
}
//------------------------------------------------------------------------------
void TextureSprite::free()
{
  //Free texture if it exists
  if( mTexture != nullptr )
  {
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
  }
}
//------------------------------------------------------------------------------
void TextureSprite::render( int x, int y, SDL_Rect* clip )
{
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  //Set clip rendering dimensions
  if( clip != nullptr )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopy( mpRenderer, mTexture, clip, &renderQuad );
}
//------------------------------------------------------------------------------
int TextureSprite::getWidth()
{
  return mWidth;
}
//------------------------------------------------------------------------------
int TextureSprite::getHeight()
{
  return mHeight;
}
//------------------------------------------------------------------------------
void TextureSprite::setColor(Uint8 aRed, Uint8 aGreen, Uint8 aBlue)
{
  SDL_SetTextureColorMod( mTexture, aRed, aGreen, aBlue );
}













