/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// https://lazyfoo.net/tutorials/SDL/13_alpha_blending/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.hpp"

const char *gTitle = "SDL Lesson 13";


//------------------------------------------------------------------------------
static SDL_Window* gWindow{ nullptr };            // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };        // The window renderer

// Screen dimension constants
constexpr int SCREEN_WIDTH { 512 };
constexpr int SCREEN_HEIGHT{ 512 };

//Scene textures
static Texture gTexture_1;
static Texture gTexture_2;
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
      //Modulation components
      //Modulation component
      Uint8 texture_1_a = 255;
      Uint8 texture_2_a = 0;

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
              case SDLK_q:
              {
                if(texture_1_a >= 255)
                  texture_1_a = 0;

                texture_1_a += 15;

                if(texture_2_a <= 0)
                  texture_2_a = 255;

                texture_2_a -= 15;
                break;
              }
              case SDLK_w:
              {
                if(texture_2_a >= 255)
                  texture_2_a = 0;

                texture_2_a += 15;

                if(texture_1_a <= 0)
                  texture_1_a = 255;

                texture_1_a -= 15;
                break;
              }
            }
          }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        gTexture_1.setAlpha(texture_1_a);
        gTexture_1.render(0, 0);

        gTexture_2.setAlpha(texture_2_a);
        gTexture_2.render(0, 0);

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
  gTexture_1.setRenderer(gRenderer);
  gTexture_2.setRenderer(gRenderer);

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  bool success = true;

  if( !gTexture_1.loadFromFile( "pics/image_1.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }
  gTexture_1.setBlendMode( SDL_BLENDMODE_BLEND );

  if( !gTexture_2.loadFromFile( "pics/image_2.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }
  gTexture_2.setBlendMode( SDL_BLENDMODE_BLEND );

  return success;
}
//------------------------------------------------------------------------------
void close()
{
  //Free loaded images
  gTexture_1.free();
  gTexture_2.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
