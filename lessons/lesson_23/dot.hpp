#ifndef _DOT_HPP_
#define _DOT_HPP_

#include <vector>
#include "texture.hpp"
#include "particle.hpp"

class dot
{
public:
  dot();
  ~dot();

  void draw();
  void move();

private:
  int m_x{ 0 };
  int m_y{ 0 };

  int m_dx{ 0 };
  int m_dy{ 0 };

  std::vector<particle> m_particles;
  texture m_texture;
};

#endif /* _DOT_HPP_ */
