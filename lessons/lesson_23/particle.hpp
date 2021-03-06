#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include "texture.hpp"

class particle
{
public:
  particle(int aX, int aY);
  ~particle();

  void draw();
  void reinit(int aX, int aY);
  bool is_dead();

private:
  void _init(int aX, int aY);

private:
  int m_x{0};
  int m_y{0};
  int m_alpha{ 0 };
  int m_alpha_dx{ 0 };
  bool m_is_dead{ true };
  size_t m_index{ 0 };
  int m_frame{0};
};

#endif /* _PARTICLE_HPP_ */