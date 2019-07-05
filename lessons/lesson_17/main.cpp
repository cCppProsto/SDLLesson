#include <stdio.h>
#include <string>

#include "renderer.hpp"

int main()
{
  renderer render(800,800,"lesson 17");

  if (!render.init())
    return 0;

  render.setBackgroundColor(100, 100, 75);
  render.run();
  
  return 0;
}
