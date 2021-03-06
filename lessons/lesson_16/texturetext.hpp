#ifndef TEXTURETEXT_HPP
#define TEXTURETEXT_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class texturetext
{
public:
  texturetext();

  void setRenderer(SDL_Renderer *apRenderer);

  bool loadFont( std::string path, int size = 24);

  void free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  void setAlpha(Uint8 alpha);

  void render(int x, int y,
              SDL_Rect* clip = nullptr,
              double angle = 0.0,
              SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE );

  void setText(std::string text);

private:
  std::string m_text;
  SDL_Color m_color;
  int mWidth{0};
  int mHeight{0};

  SDL_Renderer *mp_renderer{nullptr};
  SDL_Texture* mp_texture;
  TTF_Font  *mp_font{nullptr};
};

#endif // TEXTURETEXT_HPP
