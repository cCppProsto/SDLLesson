/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texturesprite.hpp"

const char *gTitle = "SDL Lesson 14";

//------------------------------------------------------------------------------
static SDL_Window* gWindow{ nullptr };            // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };        // The window renderer

// Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 800 };

//Scene textures
static TextureSprite gZombieTexture;
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
        SDL_SetRenderDrawColor( gRenderer, 0xF0, 0x0F, 0xF0, 0xFF );
        SDL_RenderClear( gRenderer );

        static size_t frame{0};
        static int x{600};
        static int y{200};
        static int dx{-2};
        static int dy{0};

        //Render background texture to screen
        gZombieTexture.render( x, y, frame);

        //Update screen
        SDL_RenderPresent( gRenderer );

        frame++;
        if(frame >= gZombieTexture.frameCount())
          frame = 0;

        x += dx;
        y += dy;

        if(x >= SCREEN_WIDTH || x <= 0)
          dx *= -1;

        if(y >= SCREEN_HEIGHT || y <= 0)
          dy *= -1;

        //SDL_Delay(66);
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
  bool success = true;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
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
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if( gRenderer == nullptr )
      {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
      else
      {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
          printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
          success = false;
        }
        if( TTF_Init() == -1 )
        {
          printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
          success = false;
        }
      }
    }
  }
  gZombieTexture.setRenderer(gRenderer);

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  bool success = true;

  if( !gZombieTexture.loadFromFile( "pics/zombie_moving.png", 16 ) )
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
  gZombieTexture.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
