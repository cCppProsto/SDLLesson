/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://www.lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const char *gTitle = "SDL Lesson 8";

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
static SDL_Window* gWindow{ nullptr };       // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };   // The window renderer
static SDL_Texture* gCurrentTexture{ nullptr };     // Current displayed texture

//The images that correspond to a keypress
static SDL_Texture* gKeyPressTextures[ static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL) ];

// Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 600 };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
bool init();
bool loadMedia();
SDL_Texture* loadTexture( std::string path ); //Loads individual image as texture
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

      gCurrentTexture = gKeyPressTextures[ static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT) ];

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
            gCurrentTexture = gKeyPressTextures[ index ];
          }
        }

        //Clear screen
        SDL_RenderClear( gRenderer );
        //Render texture to screen
        SDL_RenderCopy( gRenderer, gCurrentTexture, nullptr, nullptr );

        //Render red filled quad
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &fillRect );

        //Render green outlined quad
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
        SDL_RenderDrawRect( gRenderer, &outlineRect );

        //Draw blue horizontal line
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
        SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

        //Draw vertical line of yellow dots
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
        for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
        {
          SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
        }

        //Update screen
        SDL_RenderPresent( gRenderer );
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
      //Create renderer for window
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
      if( gRenderer == nullptr )
      {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
      else
      {
        //Initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
          printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
          success = false;
        }
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
  gKeyPressTextures[ index ] = loadTexture("pics/press.png" );
  if( gKeyPressTextures[ index ] == nullptr )
  {
    printf( "Failed to load default image!\n" );
    success = false;
  }

  //Load up surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_UP);
  gKeyPressTextures[ index ] = loadTexture( "pics/up.png" );
  if( gKeyPressTextures[ index ] == nullptr )
  {
    printf( "Failed to load up image!\n" );
    success = false;
  }

  //Load down surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
  gKeyPressTextures[ index ] = loadTexture( "pics/down.png" );
  if( gKeyPressTextures[ index ] == nullptr )
  {
    printf( "Failed to load down image!\n" );
    success = false;
  }

  //Load left surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
  gKeyPressTextures[ index ] = loadTexture( "pics/left.png" );
  if( gKeyPressTextures[ index ] == nullptr )
  {
    printf( "Failed to load left image!\n" );
    success = false;
  }

  //Load right surface
  index = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
  gKeyPressTextures[ index ] = loadTexture( "pics/right.png" );
  if( gKeyPressTextures[ index ] == nullptr )
  {
    printf( "Failed to load right image!\n" );
    success = false;
  }
  return success;
}
//------------------------------------------------------------------------------
SDL_Texture* loadTexture( std::string path )
{
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
    //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == nullptr )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return newTexture;
}
//------------------------------------------------------------------------------
void close()
{
  //Deallocate surfaces

  int end = static_cast<int>(eKeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL);
  for( int i = 0; i < end; ++i )
  {
    SDL_DestroyTexture( gKeyPressTextures[ i ] );
    gKeyPressTextures[ i ] = nullptr;
  }

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
