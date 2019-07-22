#include <filesystem>
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
  _load();
}
//------------------------------------------------------------------------------
settings::~settings()
{
  _save();
}
//------------------------------------------------------------------------------
void settings::_load()
{
  if (!m_file.is_open())
  {
    m_file.open("settings.stg", std::ifstream::binary | std::ifstream::ate);
    if (m_file.is_open())
    {
      size_t pos = m_file.tellg();
      if (pos == 0)
      {
        m_file.close();
        // file is empty, needs save defaults values
        std::ofstream file;
        file.open("settings.stg", std::ifstream::binary | std::ifstream::trunc);
        file << videoResolutionToInt(m_resolution) << std::endl;
        file << audioLevelToInt(m_audio_level) << std::endl;
        file.close();
      }
      else
      {
        m_file.seekg(0);
        {
          int val;
          m_file >> val;
          m_resolution = intToVideoResolution(val);
        }
        {
          int val;
          m_file >> val;
          m_audio_level = intToAudioLevel(val);
        }

      }
    }
  }
}
//------------------------------------------------------------------------------
void settings::_save()
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
int settings::audioLevelToInt(settings::eAudioLevel aLevel)
{
  switch (aLevel)
  {
    case settings::eAudioLevel::l0: { return 0; }
    case settings::eAudioLevel::l10: { return 13; }
    case settings::eAudioLevel::l20: { return 26; }
    case settings::eAudioLevel::l30: { return 38; }
    case settings::eAudioLevel::l40: { return 51; }
    case settings::eAudioLevel::l50: { return 64; }
    case settings::eAudioLevel::l60: { return 77; }
    case settings::eAudioLevel::l70: { return 90; }
    case settings::eAudioLevel::l80: { return 102; }
    case settings::eAudioLevel::l90: { return 115; }
    case settings::eAudioLevel::l100: { return 128; }
  }
  return 0;
}
//------------------------------------------------------------------------------
settings::eAudioLevel settings::intToAudioLevel(int aLevel)
{
  switch (aLevel)
  {
  case 0:   return settings::eAudioLevel::l0;
  case 13:  return settings::eAudioLevel::l10;
  case 26:  return settings::eAudioLevel::l20;
  case 38:  return settings::eAudioLevel::l30;
  case 51:  return settings::eAudioLevel::l40;
  case 64:  return settings::eAudioLevel::l50;
  case 77:  return settings::eAudioLevel::l60;
  case 90:  return settings::eAudioLevel::l70;
  case 102: return settings::eAudioLevel::l80;
  case 115: return settings::eAudioLevel::l90;
  case 128: return settings::eAudioLevel::l100;
  }
  return settings::eAudioLevel::l0;
}
//------------------------------------------------------------------------------
int settings::videoResolutionToInt(settings::eResolution aResolution)
{
  return static_cast<int>(aResolution);
}
//------------------------------------------------------------------------------
settings::eResolution settings::intToVideoResolution(int aResolution)
{
  if (aResolution >= static_cast<int>(settings::eResolution::r1920_1080))
    return settings::eResolution::r1920_1080;

  if (aResolution < static_cast<int>(settings::eResolution::r640_480))
    return settings::eResolution::r640_480;

  return settings::eResolution(int(aResolution));
}
//------------------------------------------------------------------------------
int settings::screenWidth()const
{
  switch (m_resolution)
  {
    case eResolution::r640_480:   return 640;
    case eResolution::r800_600:   return 800;
    case eResolution::r1920_1080: return 1920;
  }
  return 640;
}
//------------------------------------------------------------------------------
int settings::screenHeight()const
{
  switch (m_resolution)
  {
  case eResolution::r640_480:   return 480;
  case eResolution::r800_600:   return 600;
  case eResolution::r1920_1080: return 1080;
  }
  return 480;
}

//------------------------------------------------------------------------------
