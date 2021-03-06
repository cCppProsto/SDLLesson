/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// https://lazyfoo.net/tutorials/SDL/09_the_viewport/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const char *gTitle = "SDL Lesson 9";

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static SDL_Window* gWindow{ nullptr };            // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };        // The window renderer

static SDL_Texture* gMainTexture{ nullptr };
static SDL_Texture* gMiniMap_1{ nullptr };
static SDL_Texture* gMiniMap_2{ nullptr };

// Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 800 };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
bool init();
bool loadMedia();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

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
            switch( e.key.keysym.sym )
            {
              case SDLK_ESCAPE:
              {
                quit = true;
                break;
              }
            }
          }
        }

        //Clear screen
        SDL_RenderClear( gRenderer );

        //Top left corner viewport
        SDL_Rect topLeftViewport;
        topLeftViewport.x = 0;
        topLeftViewport.y = 0;
        topLeftViewport.w = SCREEN_WIDTH / 2;
        topLeftViewport.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport( gRenderer, &topLeftViewport );

        //Render texture to screen
        SDL_RenderCopy( gRenderer, gMainTexture, nullptr, nullptr );

        //Top right viewport
        SDL_Rect topRightViewport;
        topRightViewport.x = SCREEN_WIDTH / 2;
        topRightViewport.y = 0;
        topRightViewport.w = SCREEN_WIDTH / 2;
        topRightViewport.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport( gRenderer, &topRightViewport );

        //Render texture to screen
        SDL_RenderCopy( gRenderer, gMiniMap_1, nullptr, nullptr );

        //Bottom viewport
        SDL_Rect bottomViewport;
        bottomViewport.x = 0;
        bottomViewport.y = SCREEN_HEIGHT / 2;
        bottomViewport.w = SCREEN_WIDTH;
        bottomViewport.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport( gRenderer, &bottomViewport );

        //Render texture to screen
        SDL_RenderCopy( gRenderer, gMiniMap_2, nullptr, nullptr );

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
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

  gMainTexture = loadTexture("pics/background.png" );
  if( gMainTexture == nullptr )
  {
    printf( "Failed to load default image!\n" );
    success = false;
  }

  gMiniMap_1 = loadTexture("pics/minimap.png" );
  if( gMiniMap_1 == nullptr )
  {
    printf( "Failed to load default image!\n" );
    success = false;
  }

  gMiniMap_2 = loadTexture("pics/minimap2.png" );
  if( gMiniMap_2 == nullptr )
  {
    printf( "Failed to load default image!\n" );
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

  SDL_DestroyTexture( gMainTexture );
  SDL_DestroyTexture( gMiniMap_1 );
  SDL_DestroyTexture( gMiniMap_2 );

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
