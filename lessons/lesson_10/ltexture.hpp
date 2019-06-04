#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>

class LTexture
{
public:
  //Initializes variables
  LTexture();

  //Deallocates memory
  ~LTexture();

  void setRenderer(SDL_Renderer *apRenderer);

  //Loads image at specified path
  bool loadFromFile( std::string path);

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render( int x, int y );

  void enableColorKey();
  void disableColorKey();
  void setColorKey(Uint8 r, Uint8 g, Uint8 b);

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture{nullptr};

  SDL_Renderer *mpRenderer{nullptr};

  //Image dimensions
  int mWidth{0};
  int mHeight{0};

  bool mIsColorKeyPresent{false};
  Uint8 mColorKeyR{0};
  Uint8 mColorKeyG{0};
  Uint8 mColorKeyB{0};
};

#endif // LTEXTURE_HPP
