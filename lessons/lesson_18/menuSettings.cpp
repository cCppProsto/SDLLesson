#include "SDLEngine.hpp"

#include "settings.hpp"
#include "menuSettings.hpp"

menuSettings::eItem operator++(menuSettings::eItem &item)
{
  item = menuSettings::eItem(int(item) + 1);

  if (item > menuSettings::eItem::AudioLevel)
  {
    item = menuSettings::eItem::VideoResolution;
    return item;
  }
  return item;
}

menuSettings::eItem operator--(menuSettings::eItem &item)
{
  item = menuSettings::eItem(int(item) - 1);

  if (item > menuSettings::eItem::AudioLevel)
  {
    item = menuSettings::eItem::AudioLevel;
    return item;
  }
  return item;
}


//------------------------------------------------------------------------------
menuSettings::menuSettings()
{
  _init();
}
//------------------------------------------------------------------------------
menuSettings::~menuSettings()
{
}
//------------------------------------------------------------------------------
void menuSettings::draw()
{
  for (auto &i : mv_items)
    i.render();

  mp_resolution_item->render();
  mp_audio_level_item->render();
}
//------------------------------------------------------------------------------
void menuSettings::process()
{
  _update_resolution_items();
  _update_audio_level_items();
}
//------------------------------------------------------------------------------
void menuSettings::handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  switch (aEvent.state)
  {
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
      _unselect_current_item();
      --m_current_item;
      _select_current_item();
      break;
    }
    case SDLK_UP:
    {
      _unselect_current_item();
      ++m_current_item;
      _select_current_item();
      break;
    }
    case SDLK_RIGHT:
    {
      _right_keyboard_key_handle();
      break;
    }
    case SDLK_LEFT:
    {
      _left_keyboard_key_handle();
      break;
    }
    }
    break;
  }
  }
}
//------------------------------------------------------------------------------
void menuSettings::init()
{
  m_is_exit = false;
}
//------------------------------------------------------------------------------
const bool &menuSettings::isExit()const
{
  return m_is_exit;
}
//------------------------------------------------------------------------------
void menuSettings::_init()
{
  auto &sdl_inst{ SDLEngine::instance() };
  mv_items.resize(2);

  mv_items[0].loadFont("font/a_Albionic.ttf", 25);
  mv_items[0].setColor(255, 0, 0);
  mv_items[0].setText(u8"���������� ������");
  mv_items[0].setAlpha(m_alpha_selected);

  mv_items[1].loadFont("font/a_Albionic.ttf", 25);
  mv_items[1].setColor(255, 0, 0);
  mv_items[1].setText(u8"������� �����");
  mv_items[1].setAlpha(m_alpha_unselected);

  int y = sdl_inst.windowHeight() * 0.4;
  for (auto &i : mv_items)
  {
    int x = 50;
    i.setPos(x, y);
    y += i.height() * 2;
  }

  _init_resolution_items();
  _init_audio_level_items();
}
//------------------------------------------------------------------------------
void menuSettings::_init_resolution_items()
{
  auto &sdl_inst{ SDLEngine::instance() };

  mv_resolutions_items.resize(3);
  {
    mv_resolutions_items[0].loadFont("font/a_Albionic.ttf", 25);
    mv_resolutions_items[0].setColor(255, 0, 0);
    mv_resolutions_items[0].setText(u8"640x480");
    mv_resolutions_items[0].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_resolutions_items[0].width() - 20;
    mv_resolutions_items[0].setPos(x, mv_items[0].y());
  }

  {
    mv_resolutions_items[1].loadFont("font/a_Albionic.ttf", 25);
    mv_resolutions_items[1].setColor(255, 0, 0);
    mv_resolutions_items[1].setText(u8"800x600");
    mv_resolutions_items[1].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_resolutions_items[1].width() - 20;
    mv_resolutions_items[1].setPos(x, mv_items[0].y());
  }

  {
    mv_resolutions_items[2].loadFont("font/a_Albionic.ttf", 25);
    mv_resolutions_items[2].setColor(255, 0, 0);
    mv_resolutions_items[2].setText(u8"1920x1080");
    mv_resolutions_items[2].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_resolutions_items[2].width() - 20;
    mv_resolutions_items[2].setPos(x, mv_items[0].y());
  }
  _update_resolution_select();
}
//------------------------------------------------------------------------------
void menuSettings::_init_audio_level_items()
{
  auto &sdl_inst{ SDLEngine::instance() };

  mv_audio_levels_items.resize(11);
  size_t index{ 0 };
  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"0   %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"10  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"20  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"30  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"40  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"50  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"60  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"70  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"80  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"90  %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  {
    mv_audio_levels_items[index].loadFont("font/a_Albionic.ttf", 25);
    mv_audio_levels_items[index].setColor(255, 0, 0);
    mv_audio_levels_items[index].setText(u8"100 %");
    mv_audio_levels_items[index].setAlpha(m_alpha_unselected);
    int x = sdl_inst.windowWidth() - mv_audio_levels_items[index].width() - 20;
    mv_audio_levels_items[index].setPos(x, mv_items[1].y());
    index++;
  }

  _update_audio_level_select();
}
//------------------------------------------------------------------------------
void menuSettings::_unselect_current_item()
{
  mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_unselected);
}
//------------------------------------------------------------------------------
void menuSettings::_select_current_item()
{
  mv_items[static_cast<int>(m_current_item)].setAlpha(m_alpha_selected);
}
//------------------------------------------------------------------------------
void menuSettings::_right_keyboard_key_handle()
{
  auto &stg{ settings::instance() };
  switch (m_current_item)
  {
    case eItem::VideoResolution:
    {
      stg.setNextVideoResolution();
      break;
    }
    case eItem::AudioLevel:
    {
      stg.setNextAudioLevel();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menuSettings::_left_keyboard_key_handle()
{
  auto &stg{ settings::instance() };
  switch (m_current_item)
  {
    case eItem::VideoResolution:
    {
      stg.setPrevVideoResolution();
      break;
    }
    case eItem::AudioLevel:
    {
      stg.setPrevAudioLevel();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menuSettings::_update_resolution_select()
{
  auto &stg{ settings::instance() };

  size_t index{static_cast<size_t>(stg.resolution())};
  mv_resolutions_items[index].setAlpha(m_alpha_selected);
  mp_resolution_item = &mv_resolutions_items[index];
}
//------------------------------------------------------------------------------
void menuSettings::_uselect_resolution_values()
{
  auto &stg{ settings::instance() };

  for (auto &i : mv_resolutions_items)
    i.setAlpha(m_alpha_unselected);
}
//------------------------------------------------------------------------------
void menuSettings::_update_resolution_items()
{
  _uselect_resolution_values();

  if (m_current_item == eItem::VideoResolution)
    _update_resolution_select();
}
//------------------------------------------------------------------------------
void menuSettings::_update_audio_level_items()
{
  _uselect_audio_level_values();

  if (m_current_item == eItem::AudioLevel)
    _update_audio_level_select();
}
//------------------------------------------------------------------------------
void menuSettings::_uselect_audio_level_values()
{
  auto &stg{ settings::instance() };

  for (auto &i : mv_audio_levels_items)
    i.setAlpha(m_alpha_unselected);
}
//------------------------------------------------------------------------------
void menuSettings::_update_audio_level_select()
{
  auto &stg{ settings::instance() };

  size_t index{ static_cast<size_t>(stg.audioLevel()) };
  mv_audio_levels_items[index].setAlpha(m_alpha_selected);
  mp_audio_level_item = &mv_audio_levels_items[index];
}


