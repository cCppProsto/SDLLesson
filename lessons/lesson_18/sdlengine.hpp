#ifndef SDLENGINE_HPP
#define SDLENGINE_HPP

#include <cstddef>
#include <string>
#include <SDL2/SDL.h>

class SDLEngine
{
public:

  static void setGeometry(int aWidth, int aHeight);

  static SDLEngine &instance();

  const SDL_Renderer &renderer()const;

  const bool &isInited()const;

private:
  SDLEngine();
  ~SDLEngine();

private:
  bool m_is_inited{false};
  std::string m_last_error;
};

#endif // SDLENGINE_HPP
