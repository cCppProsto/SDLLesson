#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include <SDL.h>
#include "texture.hpp"

class BitmapFont
{
public:
  BitmapFont();
  ~BitmapFont();

  void load(std::string aPath);
  void render_text(int x, int y, std::string text);

private:
  bool _build();
  void _free();

private:
  texture m_bitmap_texture;
  SDL_Rect m_chars[256];
  int m_new_line;
  int m_space;
};

#endif /* _BITMAP_FONT_HPP_ */
