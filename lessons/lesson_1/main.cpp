/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://www.lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php

#include <iostream>
#include <SDL2/SDL.h>

//Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 600 };

using namespace std;

int main()
{
  SDL_Window  *window{ nullptr };         // The window we'll be rendering to
  SDL_Surface *screenSurface{ nullptr };  // The surface contained by the window

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
    // Create window
    window = SDL_CreateWindow( "SDL Tutorial",
                               SDL_WINDOWPOS_CENTERED_MASK,
                               SDL_WINDOWPOS_CENTERED_MASK,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN );

    if( window == nullptr )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
      // Get window surface
      screenSurface = SDL_GetWindowSurface( window );

      // Fill the surface white
      SDL_FillRect( screenSurface, nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

      // Update the surface
      SDL_UpdateWindowSurface( window );

      // Wait two seconds
      SDL_Delay( 2000 );
    }
  }

  // Destroy window
  SDL_DestroyWindow( window );

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
