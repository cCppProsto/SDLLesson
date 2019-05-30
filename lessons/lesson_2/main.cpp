/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://www.lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php

#include <iostream>
#include <SDL2/SDL.h>

//------------------------------------------------------------------------------
static SDL_Window* gWindow{nullptr};         //The window we'll be rendering to
static SDL_Surface* gScreenSurface{nullptr}; //The surface contained by the window
static SDL_Surface* gHelloWorld{nullptr};    //The image we will load and show on the screen

//Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 600 };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
bool init();
bool loadMedia();
void close();
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int main()
{
  //Start up SDL and create window
  if( !init() )
  {
    printf( "Failed to initialize!\n" );
  }
  else
  {
    //Load media
    if( !loadMedia() )
    {
      printf( "Failed to load media!\n" );
    }
    else
    {
      //Apply the image
      SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr );

      //Update the surface
      SDL_UpdateWindowSurface( gWindow );

      //Wait two seconds
      SDL_Delay( 2000 );
    }
  }

  //Free resources and close SDL
  close();

  return 0;
}

//------------------------------------------------------------------------------
bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN );

    if( gWindow == nullptr )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
  }

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load splash image
  gHelloWorld = SDL_LoadBMP( "pics/logo.bmp" );
  if( gHelloWorld == nullptr )
  {
    printf( "Unable to load image %s! SDL Error: %s\n", "pics/logo.bmp", SDL_GetError() );
    success = false;
  }
  return success;
}
//------------------------------------------------------------------------------
void close()
{
  //Deallocate surface
  SDL_FreeSurface( gHelloWorld );
  gHelloWorld = nullptr;

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;

  //Quit SDL subsystems
  SDL_Quit();
}
