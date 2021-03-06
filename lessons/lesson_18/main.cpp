#include <stdio.h>
#include <string>

#include "application.hpp"
#include "sdlengine.hpp"

int main(int argc, char* args[])
{
  SDLEngine::setGeometry(800, 800);
  SDLEngine::instance();
  SDLEngine::instance().createWindow();
  application::instace().run();

  return 0;
}
