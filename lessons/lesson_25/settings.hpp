#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <ostream>

class settings
{
public:
  enum class eResolution : uint8_t
  {
    r640_480 = 0,
    r800_600,
    r960_540,
    r1024_600,
    r1024_768,
    r1280_720,
    r1280_768,
    r1280_1024,
    r1440_900,
    r1400_1050,
    r1440_1080,
    r1600_1024,
    r1600_1200,
    r1680_1050,
    r1920_1080,
    r1920_1200,
    resolutionEnd
  };
  const std::vector< std::pair<eResolution, std::string> > mv_resolutions
  {
    { eResolution::r640_480,   "640x480"},
    { eResolution::r800_600,   "800x600"},
    { eResolution::r960_540,   "960x540"},
    { eResolution::r1024_600,  "1024x600"},
    { eResolution::r1024_768,  "1024x768"},
    { eResolution::r1280_720,  "1280x720"},
    { eResolution::r1280_768,  "1280x768"},
    { eResolution::r1280_1024, "1280x1024"},
    { eResolution::r1440_900,  "1440x900"},
    { eResolution::r1400_1050, "1400x1050"},
    { eResolution::r1440_1080, "1440x1080"},
    { eResolution::r1600_1024, "1600x1024"},
    { eResolution::r1600_1200, "1600x1200"},
    { eResolution::r1680_1050, "1680x1050"},
    { eResolution::r1920_1080, "1920x1080"},
    { eResolution::r1920_1200, "1920x1200"}
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
  const std::vector< std::pair<eAudioLevel, std::string> > mv_audio_effect_levels
  {
    { eAudioLevel::l0,   "0   %" },
    { eAudioLevel::l10,  "10  %" },
    { eAudioLevel::l20,  "20  %" },
    { eAudioLevel::l30,  "30  %" },
    { eAudioLevel::l40,  "40  %" },
    { eAudioLevel::l50,  "50  %" },
    { eAudioLevel::l60,  "60  %" },
    { eAudioLevel::l70,  "70  %" },
    { eAudioLevel::l80,  "80  %" },
    { eAudioLevel::l90,  "90  %" },
    { eAudioLevel::l100, "100 %" }
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
