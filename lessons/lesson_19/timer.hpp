#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <stdint.h>

class timer
{
public:
  timer();
  ~timer();
  void start();
  void stop();
  void pause();
  void reset();

  const bool &is_paused()const;
  const bool &is_started()const;

  const uint32_t &ticks()const;

private:
  uint32_t m_start_ticks{0};
  uint32_t m_paused_ticks{0};

  bool m_is_paused{false};
  bool m_is_started{false};
};

#endif /* _TIMER_HPP_ */
