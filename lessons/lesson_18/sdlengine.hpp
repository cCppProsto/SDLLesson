#ifndef _SDLENGINE_HPP_
#define _SDLENGINE_HPP_

#include <cstddef>
#include <string>
#include <SDL.h>

class SDLEngine
{
public:
  static void setGeometry(int aWidth, int aHeight);
  static SDLEngine &instance();
  void createWindow();

  SDL_Renderer *renderer();

  const bool &isInited()const;
  
  const int &windowWidth()const;
  const int &windowHeight()const;

private:
  SDLEngine();
  ~SDLEngine();

private:
  bool m_is_inited{ false };
  std::string m_last_error;
};

#endif // _SDLENGINE_HPP_
