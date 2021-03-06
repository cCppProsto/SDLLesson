/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://www.lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/linux/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const char *gTitle = "SDL Lesson 6";


//------------------------------------------------------------------------------
//Key press surfaces constants
enum class eKeyPressSurfaces
{
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

//------------------------------------------------------------------------------
static SDL_Window* gWindow{nullptr};         // The window we'll be rendering to
static SDL_Surface* gScreenSurface{nullptr}; // The surface contained by the window

//The images that correspond to a keypress
static SDL_Surface* gKeyPressSurfaces[ static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL) ];
static SDL_Surface* gCurrentSurface{nullptr};

//Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 600 };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
bool init();
bool loadMedia();
SDL_Surface* loadSurface( std::string path );
void close();
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int main( int argc, char* args[] )
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
      //Main loop flag
      bool quit = false;

      //Event handler
      SDL_Event e;

      gCurrentSurface = gKeyPressSurfaces[ static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT) ];

      //While application is running
      while( !quit )
      {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
          //User requests quit
          if( e.type == SDL_QUIT )
          {
            quit = true;
          }
          else if( e.type == SDL_KEYDOWN )
          {
            //Select surfaces based on key press
            int index = 0;
            switch( e.key.keysym.sym )
            {
              case SDLK_UP:
              {
                index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_UP);
                break;
              }
              case SDLK_DOWN:
              {
                index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
                break;
              }
              case SDLK_LEFT:
              {
                index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
                break;
              }
              case SDLK_RIGHT:
              {
                index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
                break;
              }
              case SDLK_ESCAPE:
              {
                quit = true;
                break;
              }
              default:
              {
                index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
                break;
              }
            }
            gCurrentSurface = gKeyPressSurfaces[ index ];
          }
        }

        //Apply the current image
        SDL_Rect stretchRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_BlitScaled( gCurrentSurface, nullptr, gScreenSurface, &stretchRect );

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
      }
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
    gWindow = SDL_CreateWindow( gTitle,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_OPENGL );

    if( gWindow == nullptr )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      int imgFlag{ IMG_INIT_PNG };
      if( !( IMG_Init( imgFlag ) & imgFlag ) )
      {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
      }
      else
      {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
      }
    }
  }

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load default surface
  int index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
  gKeyPressSurfaces[ index ] = loadSurface( "pics/press.png" );
  if( gKeyPressSurfaces[ index ] == nullptr )
  {
    printf( "Failed to load default image!\n" );
    success = false;
  }

  //Load up surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_UP);
  gKeyPressSurfaces[ index ] = loadSurface( "pics/up.png" );
  if( gKeyPressSurfaces[ index ] == nullptr )
  {
    printf( "Failed to load up image!\n" );
    success = false;
  }

  //Load down surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
  gKeyPressSurfaces[ index ] = loadSurface( "pics/down.png" );
  if( gKeyPressSurfaces[ index ] == nullptr )
  {
    printf( "Failed to load down image!\n" );
    success = false;
  }

  //Load left surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
  gKeyPressSurfaces[ index ] = loadSurface( "pics/left.png" );
  if( gKeyPressSurfaces[ index ] == nullptr )
  {
    printf( "Failed to load left image!\n" );
    success = false;
  }

  //Load right surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
  gKeyPressSurfaces[ index ] = loadSurface( "pics/right.png" );
  if( gKeyPressSurfaces[ index ] == nullptr )
  {
    printf( "Failed to load right image!\n" );
    success = false;
  }
  return success;
}
//------------------------------------------------------------------------------
SDL_Surface* loadSurface( std::string path )
{
  //The final optimized image
  SDL_Surface* optimizedSurface = nullptr;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == nullptr )
  {
    printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  }
  else
  {
    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimizedSurface == nullptr )
    {
      printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return optimizedSurface;
}
//------------------------------------------------------------------------------
void close()
{
  //Deallocate surfaces

  int end = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL);
  for( int i = 0; i < end; ++i )
  {
    SDL_FreeSurface( gKeyPressSurfaces[ i ] );
    gKeyPressSurfaces[ i ] = nullptr;
  }

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
