#include <filesystem>
#include "settings.hpp"
                     

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
  if (m_file.is_open())
  {
    m_file.close();
    std::ofstream file;
    file.open("settings.stg", std::ifstream::binary | std::ifstream::trunc);
    file << videoResolutionToInt(m_resolution) << std::endl;
    file << audioLevelToInt(m_audio_level) << std::endl;
    file.close();
  }
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
  if (int(m_resolution) == int(settings::eResolution::resolutionEnd) - 1)
    return false;
  m_resolution = settings::eResolution(int(m_resolution) + 1);
  return true;
}
//------------------------------------------------------------------------------
bool settings::setPrevVideoResolution()
{
  if (int(m_resolution) == 0)
    return false;
  m_resolution = settings::eResolution(int(m_resolution) - 1);
  return true;
}
//------------------------------------------------------------------------------
int settings::audioLevelToInt(settings::eAudioLevel aLevel)
{
  switch (aLevel)
  {
    case settings::eAudioLevel::l0:   { return 0; }
    case settings::eAudioLevel::l10:  { return 13; }
    case settings::eAudioLevel::l20:  { return 26; }
    case settings::eAudioLevel::l30:  { return 38; }
    case settings::eAudioLevel::l40:  { return 51; }
    case settings::eAudioLevel::l50:  { return 64; }
    case settings::eAudioLevel::l60:  { return 77; }
    case settings::eAudioLevel::l70:  { return 90; }
    case settings::eAudioLevel::l80:  { return 102; }
    case settings::eAudioLevel::l90:  { return 115; }
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
  if (aResolution >= static_cast<int>(settings::eResolution::resolutionEnd))
    return  settings::eResolution(int(settings::eResolution::resolutionEnd) - 1);

  if (aResolution < 0)
    return  settings::eResolution(0);

  return settings::eResolution(int(aResolution));
}
//------------------------------------------------------------------------------
int settings::screenWidth()const
{
  switch (m_resolution)
  {
    case eResolution::r640_480: return 640;
    case eResolution::r800_600: return 800;
    case eResolution::r960_540: return 960;
    case eResolution::r1024_600: return 1024;
    case eResolution::r1024_768: return 1024;
    case eResolution::r1280_720: return 1280;
    case eResolution::r1280_768: return 1280;
    case eResolution::r1280_1024: return 1280;
    case eResolution::r1440_900: return 1440;
    case eResolution::r1400_1050: return 1440;
    case eResolution::r1440_1080: return 1440;
    case eResolution::r1600_1024: return 1600;
    case eResolution::r1600_1200: return 1600;
    case eResolution::r1680_1050: return 1680;
    case eResolution::r1920_1080: return 1920;
    case eResolution::r1920_1200: return 1920;
  }
  return 640;
}
//------------------------------------------------------------------------------
int settings::screenHeight()const
{
  switch (m_resolution)
  {
    case eResolution::r640_480: return 480;
    case eResolution::r800_600: return 600;
    case eResolution::r960_540: return 540;
    case eResolution::r1024_600: return 600;
    case eResolution::r1024_768: return 768;
    case eResolution::r1280_720: return 720;
    case eResolution::r1280_768: return 768;
    case eResolution::r1280_1024: return 1024;
    case eResolution::r1440_900: return 900;
    case eResolution::r1400_1050: return 1050;
    case eResolution::r1440_1080: return 1080;
    case eResolution::r1600_1024: return 1024;
    case eResolution::r1600_1200: return 1200;
    case eResolution::r1680_1050: return 1050;
    case eResolution::r1920_1080: return 1080;
    case eResolution::r1920_1200: return 1200;
  }
  return 480;
}

//------------------------------------------------------------------------------
