#ifndef _FIRE_STREAM_H_
#define _FIRE_STREAM_H_

#include <vector>
#include <SDL_image.h>

class firestream
{
public:
  firestream();
  ~firestream();

  void load_frames(int aCount);
  void* getBuffer();

private:
  void _free();

private:
  std::vector<SDL_Surface*> m_images;
  size_t m_current_image{ 0 };
  int m_delay_frames{ 1 };
  const int m_fps{ 2 };
};

#endif /* _FIRE_STREAM_H_ */
