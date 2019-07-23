#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SDL_events.h>

class game
{
public:
  game();
  ~game();

  void draw();
  void process();
  void handle_keyboard_event(const SDL_KeyboardEvent &aEvent);
};

#endif /* _GAME_HPP_ */
