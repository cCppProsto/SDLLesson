/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ltexture.hpp"

const char *gTitle = "SDL Lesson 10";


//------------------------------------------------------------------------------
static SDL_Window* gWindow{ nullptr };            // The window we'll be rendering to
static SDL_Renderer* gRenderer{ nullptr };        // The window renderer

// Screen dimension constants
constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT{ 800 };

//Scene textures
static LTexture gFooTexture;
static LTexture gBackgroundTexture;
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
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render background texture to screen
        gBackgroundTexture.render( 0, 0 );

        //Render Foo' to the screen
        gFooTexture.render( 240, 190 );

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
  gFooTexture.setRenderer(gRenderer);
  gBackgroundTexture.setRenderer(gRenderer);

  return success;
}
//------------------------------------------------------------------------------
bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load Foo' texture
  gFooTexture.enableColorKey();
  gFooTexture.setColorKey(0, 0xff, 0xff);
  if( !gFooTexture.loadFromFile( "pics/gauntlet.png" ) )
  {
    printf( "Failed to load Foo' texture image!\n" );
    success = false;
  }

  //Load background texture
  if( !gBackgroundTexture.loadFromFile( "pics/background.png") )
  {
    printf( "Failed to load background texture image!\n" );
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
  //Free loaded images
  gFooTexture.free();
  gBackgroundTexture.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
