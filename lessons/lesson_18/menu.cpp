
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
  _load_sound();
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
    for (auto &i : mv_items)
      i.render();
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
          mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_unselected);
          ++m_current_item;
          mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_selected);

          _sdl.play_menu_item_change();
          break;
        }
        case SDLK_UP:
        {
          mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_unselected);
          --m_current_item;
          mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_selected);

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
  int window_x_center{ SDLEngine::instance().windowWidth() / 2 };

  mv_items.resize(4);
  
  mv_items[0].loadFont("resources/fonts/a_Albionic.ttf", 32);
  mv_items[0].setColor(255, 0, 0);
  mv_items[0].setText(u8"старт");
  mv_items[0].setAlpha(m_alpha_selected);

  mv_items[1].loadFont("resources/fonts/a_Albionic.ttf", 32);
  mv_items[1].setColor(255, 0, 0);
  mv_items[1].setText(u8"настройки");
  mv_items[1].setAlpha(m_alpha_unselected);

  mv_items[2].loadFont("resources/fonts/a_Albionic.ttf", 32);
  mv_items[2].setColor(255, 0, 0);
  mv_items[2].setText(u8"авторы");
  mv_items[2].setAlpha(m_alpha_unselected);

  mv_items[3].loadFont("resources/fonts/a_Albionic.ttf", 32);
  mv_items[3].setColor(255, 0, 0);
  mv_items[3].setText(u8"выход");
  mv_items[3].setAlpha(m_alpha_unselected);

  int y = SDLEngine::instance().windowWidth() * 0.25;
  for (auto &i : mv_items)
  {
    int x = window_x_center - i.width() / 2;
    i.setPos(x, y);
    y += i.height() * 2;
  }
}
//------------------------------------------------------------------------------
void menu::_load_sound()
{
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




