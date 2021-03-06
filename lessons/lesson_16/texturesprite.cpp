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
bool TextureSprite::loadFromFile( std::string path, size_t aFrameCount)
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
      mWidth = static_cast<size_t>(loadedSurface->w) / aFrameCount;
      mHeight = static_cast<size_t>(loadedSurface->h);
      mFrameCount = aFrameCount;
      mvRects.resize(aFrameCount);

      int x = 0;

      for(auto &r : mvRects)
      {
        r.x = x;
        r.y = 0;
        r.w = static_cast<int>(mWidth);
        r.h = static_cast<int>(mHeight);

        x += mWidth;
      }
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
void TextureSprite::render( int x, int y, size_t aFrameNumber )
{
  SDL_Rect renderQuad = {
                          x,
                          y,
                          static_cast<int>(mWidth),
                          static_cast<int>(mHeight)
                        };

  //Render to screen
  SDL_RenderCopy( mpRenderer, mTexture, &mvRects[aFrameNumber], &renderQuad );
}
//------------------------------------------------------------------------------
size_t TextureSprite::getWidth()
{
  return mWidth;
}
//------------------------------------------------------------------------------
size_t TextureSprite::getHeight()
{
  return mHeight;
}
//------------------------------------------------------------------------------
size_t TextureSprite::frameCount()
{
  return mFrameCount;
}
