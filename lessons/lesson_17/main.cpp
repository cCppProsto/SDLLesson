#include <stdio.h>
#include <string>

#include "renderer.hpp"

//  angle = atan2(mouseY - knobCenterY, mouseX - knobCenterX)
int main(int argc, char* args[])
{
  renderer render(800,800,"lesson 17");

  if (!render.init())
    return 0;

  render.setBackgroundColor(55, 10, 25);
  render.run();
  
  return 0;
}
