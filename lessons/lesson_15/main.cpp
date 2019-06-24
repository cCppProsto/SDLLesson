/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://lazyfoo.net/tutorials/SDL/15_rotation_and_flipping/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.hpp"

const char *gTitle = "SDL Lesson 15";

//------------------------------------------------------------------------------
static SDL_Window* gWindow{ nullptr };            // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };        // The window renderer

// Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 800 };

//Scene textures
static Texture gCompasTexture;
static Texture gArrowTexture;
static Texture gSoldierTexture;
//------------------------------------------------------------------------------
bool init();
bool loadMedia();

//Loads individual image as texture

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

      //Angle of rotation
      double degrees = 0;

      //Flip type
      int flipType = SDL_FLIP_NONE;

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
              case SDLK_a:
              {
                degrees -= 7;
                break;
              }
              case SDLK_d:
              {
                degrees += 7;
                break;
              }
              case SDLK_q:
              {
                flipType = SDL_FLIP_HORIZONTAL;
                break;
              }
              case SDLK_w:
              {
                flipType = SDL_FLIP_NONE;
                break;
              }
              case SDLK_e:
              {
                flipType = SDL_FLIP_VERTICAL;
                break;
              }
              case SDLK_r:
              {
                flipType = SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL;
                break;
              }
            }
          }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xF0, 0xFF, 0xF0, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render background texture to screen
        gCompasTexture.render(( SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2,
                              ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2);

        gArrowTexture.render( ( SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2,
                              ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2,
                              nullptr,
                              degrees);

        gSoldierTexture.render( 0,
                                0,
                                nullptr,
                                0.0,
                                nullptr,
                                (SDL_RendererFlip)flipType );

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
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
  gArrowTexture.setRenderer(gRenderer);
  gCompasTexture.setRenderer(gRenderer);
  gSoldierTexture.setRenderer(gRenderer);

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  bool success = true;

  if( !gArrowTexture.loadFromFile( "pics/arrow.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }

  if( !gCompasTexture.loadFromFile( "pics/compass.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }

  if( !gSoldierTexture.loadFromFile( "pics/soldier.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }
  return success;
}
//------------------------------------------------------------------------------
void close()
{
  //Free loaded images
  gArrowTexture.free();
  gCompasTexture.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
