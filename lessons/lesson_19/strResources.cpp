#include "strResources.hpp"

#include <codecvt>

#ifdef _WIN32


#include <Windows.h>
static std::string wstrtostr(const std::wstring &wstr)
{
  std::string strTo;
  char *szTo = new char[wstr.length() + 1];
  szTo[wstr.size()] = '\0';
  WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
  strTo = szTo;
  delete[] szTo;
  return strTo;
}
#endif

//------------------------------------------------------------------------------
const std::string &strResources::start_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"старт") };
  return res;
#else
  static std::string res{ u8"старт" };
  return res;
#endif
}
//------------------------------------------------------------------------------
const std::string &strResources::settings_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"настройки") };
  return res;
#else
  static std::string res{ u8"настройки" };
  return res;
#endif
}
//------------------------------------------------------------------------------
const std::string &strResources::authors_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"авторы") };
  return res;
#else
  static std::string res{ u8"авторы" };
  return res;
#endif
}
//------------------------------------------------------------------------------
const std::string &strResources::exit_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"выход") };
  return res;
#else
  static std::string res{ u8"выход" };
  return res;
#endif
}
//------------------------------------------------------------------------------
const std::string &strResources::screen_resolution_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"разрешение экрана") };
  return res;
#else
  static std::string res{ u8"выход" };
  return res;
#endif
}
//------------------------------------------------------------------------------
const std::string &strResources::level_sound_u8()
{
#ifdef _WIN32
  static std::string res{ wstrtostr(L"уровень звука") };
  return res;
#else
  static std::string res{ u8"выход" };
  return res;
#endif
}


