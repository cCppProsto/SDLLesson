#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <string>
#include <SDL.h>

class texture
{
public:
  texture();
  ~texture();

  bool load(const std::string &aPath);
  void setPosition(int aX, int aY);
  void set_alpha(uint8_t aAlpha);
  void draw();

  const int &width()const;
  const int &height()const;

private:
  void _free();

private:
  int m_x{ 0 };
  int m_y{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };
  
  SDL_Texture *m_texture{nullptr};
};

#endif /* _TEXTURE_HPP_ */
