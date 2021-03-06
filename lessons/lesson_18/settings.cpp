#include "settings.hpp"



/*
sResolution m_resolutions[3] =
{
  settings::eResolution::r640_480,   "640x480",
  settings::eResolution::r800_600,   "800x600",
  settings::eResolution::r1920_1080, "1920x1080"
};

sAudioLevel m_resolutions[10] =
{
  settings::eAudioLevel::l10,   "10",
  settings::eAudioLevel::l20,   "20",
  settings::eAudioLevel::l30,   "30",
  settings::eAudioLevel::l40,   "40",
  settings::eAudioLevel::l50,   "50",
  settings::eAudioLevel::l60,   "60",
  settings::eAudioLevel::l70,   "70",
  settings::eAudioLevel::l80,   "80",
  settings::eAudioLevel::l90,   "90",
  settings::eAudioLevel::l100,  "100"
};
*/


settings::eResolution operator++(settings::eResolution &item)
{
  item = settings::eResolution(int(item) + 1);

  if (item > settings::eResolution::r1920_1080)
    item = settings::eResolution::r1920_1080;

  return item;
}

settings::eResolution operator--(settings::eResolution &item)
{
  item = settings::eResolution(int(item) - 1);

  if (item > settings::eResolution::r1920_1080)
    item = settings::eResolution::r640_480;

  return item;
}


//------------------------------------------------------------------------------
settings &settings::instance()
{
  static settings res;
  return res;
}
//------------------------------------------------------------------------------
settings::settings()
{
}
//------------------------------------------------------------------------------
settings::~settings()
{
}
//------------------------------------------------------------------------------
const settings::eAudioLevel &settings::audioLevel()const
{
  return m_audio_level;
}
//------------------------------------------------------------------------------
const settings::eResolution &settings::resolution()const
{
  return m_resolution;
}
//------------------------------------------------------------------------------
bool settings::setNextAudioLevel()
{
  if (m_audio_level == settings::eAudioLevel::l100)
    return false;

  m_audio_level = settings::eAudioLevel(int(m_audio_level) + 1);

  return true;
}
//------------------------------------------------------------------------------
bool settings::setPrevAudioLevel()
{
  if (m_audio_level == settings::eAudioLevel::l0)
    return false;
  m_audio_level = settings::eAudioLevel(int(m_audio_level) - 1);
  return true;
}
//------------------------------------------------------------------------------
bool settings::setNextVideoResolution()
{
  if (m_resolution == settings::eResolution::r1920_1080)
    return false;
  m_resolution = settings::eResolution(int(m_resolution) + 1);
  return true;
}
//------------------------------------------------------------------------------
bool settings::setPrevVideoResolution()
{
  if (m_resolution == settings::eResolution::r640_480)
    return false;
  m_resolution = settings::eResolution(int(m_resolution) - 1);
  return true;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
