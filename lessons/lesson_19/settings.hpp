#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <stdint.h>
#include <string>
#include <utility>
#include <fstream>
#include <ostream>

class settings
{
public:
  enum class eResolution : uint8_t
  {
    r640_480,
    r800_600,
    r1920_1080
  };

  /*
  SDL volume - The volume to use from 0 to MIX_MAX_VOLUME(128).
  */
  enum class eAudioLevel : uint8_t
  {
    l0,
    l10,
    l20,
    l30,
    l40,
    l50,
    l60,
    l70,
    l80,
    l90,
    l100
  };

public:
  static settings &instance();

  bool setNextAudioLevel();
  bool setPrevAudioLevel();

  bool setNextVideoResolution();
  bool setPrevVideoResolution();

  const eAudioLevel &audioLevel()const;
  const eResolution &resolution()const;

  int screenWidth()const;
  int screenHeight()const;

  int audioLevelToInt(eAudioLevel aLevel);
  eAudioLevel intToAudioLevel(int aLevel);

  int videoResolutionToInt(eResolution aResolution);
  eResolution intToVideoResolution(int aResolution);

private:
  settings();
  ~settings();

  void _load();
  void _save();

private:
  eResolution m_resolution{ settings::eResolution::r640_480};
  eAudioLevel m_audio_level{ settings::eAudioLevel::l50 };

  std::ifstream m_file;
};


#endif /* _SETTINGS_HPP_ */
