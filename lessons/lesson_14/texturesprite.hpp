#ifndef TEXTURESPRITE_HPP
#define TEXTURESPRITE_HPP


#include <string>
#include <vector>
#include <SDL2/SDL.h>

class TextureSprite
{
public:
  TextureSprite();

  ~TextureSprite();

  void setRenderer(SDL_Renderer *apRenderer);

  bool loadFromFile( std::string path, size_t frameCount);

  void free();

  void render( int x, int y, size_t frameNumber );

  size_t getWidth();
  size_t getHeight();
  size_t frameCount();

private:
  SDL_Texture* mTexture{nullptr};
  SDL_Renderer *mpRenderer{nullptr};

  size_t mWidth{0};
  size_t mHeight{0};
  size_t mFrameCount{0};

  std::vector<SDL_Rect> mvRects;
};

#endif // TEXTURESPRITE_HPP
