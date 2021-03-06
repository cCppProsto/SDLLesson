#include "ltexture.hpp"

#include <SDL2/SDL_image.h>

//------------------------------------------------------------------------------
LTexture::LTexture()
{
}
//------------------------------------------------------------------------------
LTexture::~LTexture()
{
  free();
}
//------------------------------------------------------------------------------
void LTexture::setRenderer(SDL_Renderer *apRenderer)
{
  mpRenderer = apRenderer;
}
//------------------------------------------------------------------------------
bool LTexture::loadFromFile( std::string path )
{
  //Get rid of preexisting texture
  free();

  //The final texture
  SDL_Texture* newTexture = nullptr;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == nullptr )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  }
  else
  {
    //Color key image
    if(mIsColorKeyPresent)
      SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, mColorKeyR, mColorKeyG, mColorKeyB ) );

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( mpRenderer, loadedSurface );
    if( newTexture == nullptr )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
      //Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  //Return success
  mTexture = newTexture;
  return mTexture != nullptr;
}
//------------------------------------------------------------------------------
void LTexture::free()
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
void LTexture::render( int x, int y )
{
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  SDL_RenderCopy( mpRenderer, mTexture, nullptr, &renderQuad );
}
//------------------------------------------------------------------------------
void LTexture::enableColorKey()
{
  mIsColorKeyPresent = true;
}
//------------------------------------------------------------------------------
void LTexture::disableColorKey()
{
  mIsColorKeyPresent = false;
}
//------------------------------------------------------------------------------
void LTexture::setColorKey(Uint8 r, Uint8 g, Uint8 b)
{
  mColorKeyR = r;
  mColorKeyG = g;
  mColorKeyB = b;
}
//------------------------------------------------------------------------------
int LTexture::getWidth()
{
  return mWidth;
}
//------------------------------------------------------------------------------
int LTexture::getHeight()
{
  return mHeight;
}
