#ifndef _GOBLIN_SURFACE_H_
#define _GOBLIN_SURFACE_H_

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class goblinSurface 
{
public:
  enum class eDirection
  {
    Left = 0,
    Left_Up,
    Up,
    Up_Right,
    Right,
    Right_Down,
    Down,
    Down_Left
  };

public:
  goblinSurface();
  ~goblinSurface();

  void setPosition(int aX, int aY);

  void handleEvent(SDL_Event &aEvent) ;
  void draw() const;
  void process();

  void loadTexture();
  void setDirection(eDirection aDirection);

  void move();
  void stop();
  void attack();

  const int &x()const;
  const int &y()const;

  const int &x_center()const;
  const int &y_center()const;

  const int &x_right()const;
  const int &y_down()const;

  const size_t &width()const;
  const size_t &height()const;

private:
  void _free();
  void _update_geometry_values();

  std::vector<SDL_Rect> &_get_rects(eDirection aDirection);

private:
  int m_x{ 0 };
  int m_y{ 0 };
  int m_x_right{0};
  int m_y_down{ 0 };
  int m_x_center{ 0 };
  int m_y_center{ 0 };

  size_t m_current_frame{ 0 };
  size_t m_frame_count{ 0 };

  size_t m_width{ 0 };
  size_t m_height{ 0 };

  bool m_data_is_loaded{ false };
  bool m_is_moving{false};
  bool m_is_attack{ false };

  eDirection m_direction;

  SDL_Rect *mp_current_rect{ nullptr };

  SDL_Texture* mp_texture{nullptr};

  std::vector< std::vector<SDL_Rect> > mv_sprite_rects;
};

#endif /* _GOBLIN_SURFACE_H_ */
