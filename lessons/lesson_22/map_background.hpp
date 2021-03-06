#ifndef _MAP_BACKGROUND_HPP_
#define _MAP_BACKGROUND_HPP_

#include <SDL.h>

class map_background
{
public:
  map_background();
  ~map_background();

  void draw(const SDL_Rect *aCamera) const;
  const float &width()const;
  const float &height()const;

private:
  void _load_texture();
  void  _free();

private:
  float m_x{ 0 };
  float m_y{ 0 };
  float m_original_width{ 0 };
  float m_original_height{ 0 };
  float m_width{ 0 };
  float m_height{ 0 };

  SDL_Texture* mp_texture{ nullptr };
};

#endif /* _MAP_BACKGROUND_HPP_ */
