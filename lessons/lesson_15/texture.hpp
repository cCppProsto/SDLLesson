#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Texture
{
public:
  Texture();

  ~Texture();

  void setRenderer(SDL_Renderer *apRenderer);

  bool loadFromFile( std::string path);

  void free();

  void render( int x,
               int y,
               SDL_Rect* clip = nullptr,
               double angle = 0.0,
               SDL_Point* center = nullptr,
               SDL_RendererFlip flip = SDL_FLIP_NONE );

  void setColor(Uint8 aRed, Uint8 aGreen, Uint8 aBlue);

  void setBlendMode( SDL_BlendMode blending );

  void setAlpha( Uint8 alpha );

  int getWidth();
  int getHeight();

private:
  SDL_Texture* mTexture{nullptr};
  SDL_Renderer *mpRenderer{nullptr};

  int mWidth{0};
  int mHeight{0};

  SDL_Rect mvRect;
};

#endif // TEXTURE_HPP
