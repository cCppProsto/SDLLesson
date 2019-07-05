#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <cstddef>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "goblinSurface.hpp"

class renderer
{
public:
  renderer(size_t aWidth, size_t aHeight, std::string aTitle);
  ~renderer();

  bool init();
  void run();

  void setBackgroundColor(uint8_t aR, uint8_t aG, uint8_t aB);

  static SDL_Renderer *sdl_renderer();

private:
  void _init_objects();
  void _event_handle();
  void _process();
  void _draw();

private:
  uint8_t m_background_r{ 0 };
  uint8_t m_background_g{ 0 };
  uint8_t m_background_b{ 0 };

  bool m_is_inited{ false };
  bool m_is_exit{ false };
  size_t m_width{0};
  size_t m_height{ 0 };
  
  std::string m_window_title;
  std::string m_str_last_error;
  
  goblinSurface m_goblin;

  static SDL_Window   *mp_window;
  static SDL_Renderer *mp_renderer;
};

#endif /* _RENDERER_H_ */
