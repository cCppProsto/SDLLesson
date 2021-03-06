#ifndef _BALL_HPP_
#define _BALL_HPP_

#include <SDL.h>
#include <vector>

#include "block.hpp"

class ball
{
public:
  ball();
  ~ball();

  void move();
  void draw();
  
  void add_horizontal_block(const block &aBlock);
  void add_vertical_block(const block &aBlock);

  void set_position(float aX, float aY);

  const int &x()const;
  const int &y()const;
  const int &width()const;
  const int &height()const;

private:
  void _load_texture();
  void _free();
  bool _is_collision_with_horizontal_block();
  bool _is_collision_with_vertical_block();

private:
  float m_x{ 0 };
  float m_y{ 0 };
  int m_original_width{ 0 };
  int m_original_height{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };

  float m_dx{ 1.0f };
  float m_dy{ 1.0f };
  float m_speed{ 1.0f };

  SDL_Texture* mp_texture{ nullptr };
  
  std::vector<const block *> mvp_h_blocks;
  std::vector<const block *> mvp_v_blocks;
};


#endif /* _BALL_HPP_ */
