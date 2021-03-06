#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_


#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextureText
{
public:
  TextureText();
  ~TextureText();

  bool loadFont(std::string path, int size = 24);

  void setColor(Uint8 red, Uint8 green, Uint8 blue);
  void setPos(int x, int y);
  void setAlpha(Uint8 alpha);
  void render(double angle = 0.0);
  void setText(std::string text);

  const int &width()const;
  const int &height()const;
  const int &x()const;
  const int &y()const;

private:
  void _free();

private:
  int m_x{ 0 };
  int m_y{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };

  std::string m_text;
  std::string m_last_error;

  SDL_Color m_color;
  SDL_Texture *mp_texture{ nullptr };
  TTF_Font *mp_font{ nullptr };
};

#endif /* _TEXTURE_HPP_ */
