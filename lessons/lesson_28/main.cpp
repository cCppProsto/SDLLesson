#include <stdio.h>
#include <string>
#include <clocale>
#include <GL/glut.h>

#include "application.hpp"
#include "sdlengine.hpp"

int main(int argc, char* args[])
{
  glutInit(&argc, args);
  SDLEngine::instance().createWindow();
  application::instace().run();

  return 0;
}

