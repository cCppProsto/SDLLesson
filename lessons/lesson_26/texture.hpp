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
  void draw(int x, int y, SDL_Rect* clip = nullptr);

  const int &width()const;
  const int &height()const;
  
  bool create_blank(int aWidth, int aHeight);
  Uint32 get_pixel32(unsigned int x, unsigned int y);
  bool lock();
  bool unlock();
  void copy_pixels(void* pixels);

private:
  void _free();

private:
  int m_x{ 0 };
  int m_y{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };
  int m_pitch{ 0 };
  
  void *mp_pixels{ nullptr };
  SDL_Texture *m_texture{nullptr};
};

#endif /* _TEXTURE_HPP_ */
