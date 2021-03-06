#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <SDL.h>

class block
{
public:
  block();
  ~block();

  void set_horizontal();
  void set_vertical();
  void set_position(int aX, int aY);

  void move_left();
  void move_right();
  void move_up();
  void move_down();
  void draw();

  const float &x()const;
  const float &y()const;
  const float &width()const;
  const float &height()const;

private:
  void _load_vertical_texture(const char *aTexturePath);
  void _load_horizontal_texture(const char *aTexturePath);
  void _free();

private:
  float m_x{ 0 };
  float m_y{ 0 };
  float m_original_width{ 0 };
  float m_original_height{ 0 };
  float m_width{ 0 };
  float m_height{ 0 };
  float m_dx{ 0 };
  float m_dy{ 0 };

  SDL_Texture* mp_texture{ nullptr };
};

#endif /* _BLOCK_HPP_ */
