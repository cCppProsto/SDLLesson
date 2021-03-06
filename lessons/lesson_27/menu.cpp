#include <codecvt>
#include <GL/glut.h>
#include "sdlengine.hpp"
#include "menu.hpp"

menu::eItem operator++(menu::eItem &item)
{
  item = menu::eItem(int(item) + 1);

  if (item > menu::eItem::Exit)
    item = menu::eItem::Start;
  return item;
}

menu::eItem operator--(menu::eItem &item)
{
  item = menu::eItem(int(item) - 1);

  if (item > menu::eItem::Exit)
    item = menu::eItem::Exit;
  return item;
}


//------------------------------------------------------------------------------
menu::menu()
{
  _init_text();
}
//------------------------------------------------------------------------------
menu::~menu()
{
}
//------------------------------------------------------------------------------
void menu::draw()
{
  if (m_is_high_level)
  {
    float x = SDLEngine::instance().windowWidth() * 0.4f;
    float y = SDLEngine::instance().windowWidth() * 0.3f;
    for (int i = 0; i < mv_items.size(); ++i)
    {
      if(i == (int)m_current_item)
        glColor3ub(255, 50, 55);
      else
        glColor3ub(255, 255, 255);

      glRasterPos2f(x, y);
      for (auto c : mv_items[i])
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
      y += 50;
    }
    return;
  }

  switch (m_current_item)
  {
    case eItem::Start:
    {
      break;
    }
    case eItem::Settings:
    {
      m_settings_page.draw();
      break;
    }
    case eItem::Authors:
    {
      break;
    }
    case eItem::Exit:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menu::process()
{
  if (m_is_high_level)
  {
    return;
  }

  switch (m_current_item)
  {
    case eItem::Start:
    case eItem::Exit:
      break;
    case eItem::Settings:
    {
      m_settings_page.process();
      if (!m_settings_page.isActive())
      {
        m_is_high_level = true;
        SDLEngine::instance().play_menu_background_music();
      }
      break;
    }
    case eItem::Authors:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menu::handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  const auto &_sdl{ SDLEngine::instance() };

  if (m_is_high_level)
  {
    switch (aEvent.state)
    {
      case SDL_PRESSED:
      {
        break;
      }
      case SDL_RELEASED:
      {
        switch (aEvent.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
          m_is_exit = true;
          break;
        }
        case SDLK_DOWN:
        {
          ++m_current_item;
          _sdl.play_menu_item_change();
          break;
        }
        case SDLK_UP:
        {
          --m_current_item;
          _sdl.play_menu_item_change();
          break;
        }
        case SDLK_RETURN:
        {
          _change_state();
          break;
        }
        }
        break;
      }
    }
    return;
  }

  switch (m_current_item)
  {
    case eItem::Start:
    case eItem::Exit:
      break;
    case eItem::Settings:
    {
      m_settings_page.handle_keyboard_event(aEvent);
      break;
    }
    case eItem::Authors:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
const bool &menu::isExit()const
{
  return m_is_exit;
}
//------------------------------------------------------------------------------
void menu::_init_text()
{
  float window_x_center{ static_cast<int>(SDLEngine::instance().windowWidth()) / 2.f };

  mv_items.resize(4);
  
  mv_items[0] = "Start";
  mv_items[1] = "Settings";
  mv_items[2] = "Authors";
  mv_items[3] = "Exit";
}
//------------------------------------------------------------------------------
void menu::_change_state()
{
  const auto &_sdl{ SDLEngine::instance() };

  switch (m_current_item)
  {
    case eItem::Start:
    {
      m_is_high_level = false;
      m_is_start = true;
      _sdl.play_menu_game_start();
      break;
    }
    case eItem::Settings:
    {
      m_is_high_level = false;
      SDLEngine::instance().pause_menu_background_music();
      _sdl.play_menu_item_enter();
      m_settings_page.init();
      break;
    }
    case eItem::Authors:
    {
      m_is_high_level = false;
      break;
    }
    case eItem::Exit:
    {
      m_is_exit = true;
      break;
    }
  }
}
//------------------------------------------------------------------------------
const bool &menu::isGameStart()const
{
  return m_is_start;
}
//------------------------------------------------------------------------------
void menu::reset_flags()
{
  m_is_exit = false;
  m_is_high_level = true;
  m_is_start = false;
}





