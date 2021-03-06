#include <GL/glut.h>

#include "sdlengine.hpp"
#include "settings.hpp"
#include "menuSettings.hpp"

menuSettings::eItem operator++(menuSettings::eItem &item)
{
  item = menuSettings::eItem(int(item) + 1);

  if (item > menuSettings::eItem::AudioLevel)
    item = menuSettings::eItem::VideoResolution;

  return item;
}

menuSettings::eItem operator--(menuSettings::eItem &item)
{
  item = menuSettings::eItem(int(item) - 1);

  if (item > menuSettings::eItem::AudioLevel)
    item = menuSettings::eItem::AudioLevel;

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
  {
    float x = SDLEngine::instance().windowWidth() * 0.2f;
    float y = SDLEngine::instance().windowWidth() * 0.3f;
    for (int i = 0; i < mv_items.size(); ++i)
    {
      if (i == (int)m_current_item)
        glColor3ub(255, 50, 55);
      else
        glColor3ub(255, 255, 255);

      glRasterPos2f(x, y);
      for (auto c : mv_items[i])
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
      y += 50;
    }
  }

  float x = SDLEngine::instance().windowWidth() * 0.5f;
  float y = SDLEngine::instance().windowWidth() * 0.3f;

  auto &stg{ settings::instance() };
  size_t index{ static_cast<size_t>(stg.resolution()) };
  if (m_current_item == eItem::VideoResolution)
    glColor3ub(255, 50, 55);
  else
    glColor3ub(255, 255, 255);

  glRasterPos2f(x, y);
  for (auto c : mv_resolutions_items[index])
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

  y += 50;
  index = static_cast<size_t>(stg.audioLevel()) ;
  if (m_current_item == eItem::AudioLevel)
    glColor3ub(255, 50, 55);
  else
    glColor3ub(255, 255, 255);

  glRasterPos2f(x, y);
  for (auto c : mv_audio_levels_items[index])
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}
//------------------------------------------------------------------------------
void menuSettings::process()
{
}
//------------------------------------------------------------------------------
void menuSettings::handle_keyboard_event(const SDL_KeyboardEvent &aEvent)
{
  const auto &_sdl{ SDLEngine::instance() };

  switch (aEvent.state)
  {
    case SDL_RELEASED:
    {
      switch (aEvent.keysym.sym)
      {
        case SDLK_ESCAPE:
        {
          m_is_active = false;
          break;
        }
        case SDLK_DOWN:
        {
          _sdl.play_menu_item_change();
          --m_current_item;
          break;
        }
        case SDLK_UP:
        {
          _sdl.play_menu_item_change();
          ++m_current_item;
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
  m_is_active = true;
}
//------------------------------------------------------------------------------
const bool &menuSettings::isActive()const
{
  return m_is_active;
}
//------------------------------------------------------------------------------
void menuSettings::_init()
{
  auto &sdl_inst{ SDLEngine::instance() };
  mv_items.resize(2);
  mv_items[0] = "Screen resolutions";
  mv_items[1] = "audio level";

  _init_resolution_items();
  _init_audio_level_items();
}
//------------------------------------------------------------------------------
void menuSettings::_init_resolution_items()
{
  auto &sdl_inst{ SDLEngine::instance() };

  mv_resolutions_items.resize(settings::instance().mv_resolutions.size());
  for(size_t i = 0; i < mv_resolutions_items.size(); ++i)
    mv_resolutions_items[i] = settings::instance().mv_resolutions[i].second;
}
//------------------------------------------------------------------------------
void menuSettings::_init_audio_level_items()
{
  auto &sdl_inst{ SDLEngine::instance() };

  mv_audio_levels_items.resize(settings::instance().mv_audio_effect_levels.size());
  for (size_t i = 0; i < mv_audio_levels_items.size(); ++i)
    mv_audio_levels_items[i] = settings::instance().mv_audio_effect_levels[i].second;
}
//------------------------------------------------------------------------------
void menuSettings::_right_keyboard_key_handle()
{
  auto &stg{ settings::instance() };
  auto &sdl{ SDLEngine::instance() };
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
      sdl.setAudioVolume(stg.audioLevel());
      sdl.play_menu_settings_change_audio_level();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menuSettings::_left_keyboard_key_handle()
{
  auto &stg{ settings::instance() };
  auto &sdl{ SDLEngine::instance() };
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
      sdl.setAudioVolume(stg.audioLevel());
      sdl.play_menu_settings_change_audio_level();
      break;
    }
  }
}


