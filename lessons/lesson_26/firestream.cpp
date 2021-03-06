#include <string>

#include "firestream.hpp"

firestream::firestream()
{
}
//------------------------------------------------------------------------------
firestream::~firestream()
{
  _free();
}
//------------------------------------------------------------------------------
void firestream::_free()
{
  for (auto &v : m_images)
  {
    SDL_FreeSurface(v);
    v = nullptr;
  }
  m_images.clear();
}
//------------------------------------------------------------------------------
void firestream::load_frames(int aCount)
{
  _free();

  m_images.resize(aCount);

  std::string path{"resources/pics/fire_frames/256x256/"};
  path += std::to_string(aCount);
  path += " frames/";
  
  size_t index = 1;
  if (aCount == 75)
    index = 51;

  for (auto &v : m_images)
  {
    char file_name[64] = "";

    if (aCount == 75)
      sprintf(file_name, "fire1_%04d.png", index);
    else
      sprintf(file_name, "fire1_ %02d.png", index);

    SDL_Surface* loadedSurface = IMG_Load(std::string(path + file_name).c_str());
    if (loadedSurface != nullptr)
      v = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);

    SDL_FreeSurface(loadedSurface);
    index++;
  }
}
//------------------------------------------------------------------------------
void *firestream::getBuffer()
{
  --m_delay_frames;
  if (m_delay_frames == 0)
  {
    ++m_current_image;
    m_delay_frames = m_fps;

    if (m_current_image == m_images.size())
    {
      m_current_image = 0;
    }
  }

  return m_images[m_current_image]->pixels;
}
//------------------------------------------------------------------------------
