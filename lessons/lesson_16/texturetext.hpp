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

  bool loadFont( std::string path);

  void free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  void render( std::string text, int x, int y);
};

#endif // TEXTURETEXT_HPP
