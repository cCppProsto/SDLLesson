#include <stdio.h>
#include <string>
#include <clocale>

#include "application.hpp"
#include "sdlengine.hpp"

int main(int argc, char* args[])
{
  SDLEngine::instance().createWindow();
  application::instace().run();

  return 0;
}

