#include "texture.hpp"

#include <SDL2/SDL_image.h>

//------------------------------------------------------------------------------
Texture::Texture()
{

}
//------------------------------------------------------------------------------
Texture::~Texture()
{
  free();
}
//------------------------------------------------------------------------------
void Texture::setRenderer(SDL_Renderer *apRenderer)
{
  mpRenderer = apRenderer;
}
//------------------------------------------------------------------------------
bool Texture::loadFromFile( std::string path)
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
void Texture::free()
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
void Texture::render( int x,
                      int y,
                      SDL_Rect* clip,
                      double angle,
                      SDL_Point* center,
                      SDL_RendererFlip flip)
{
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  //Set clip rendering dimensions
  if( clip != nullptr )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx( mpRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
//------------------------------------------------------------------------------
int Texture::getWidth()
{
  return mWidth;
}
//------------------------------------------------------------------------------
int Texture::getHeight()
{
  return mHeight;
}
//------------------------------------------------------------------------------
void Texture::setColor(Uint8 aRed, Uint8 aGreen, Uint8 aBlue)
{
  SDL_SetTextureColorMod( mTexture, aRed, aGreen, aBlue );
}
//------------------------------------------------------------------------------
void Texture::setBlendMode( SDL_BlendMode blending )
{
  SDL_SetTextureBlendMode( mTexture, blending );
}
//------------------------------------------------------------------------------
void Texture::setAlpha( Uint8 alpha )
{
   SDL_SetTextureAlphaMod( mTexture, alpha );
}












