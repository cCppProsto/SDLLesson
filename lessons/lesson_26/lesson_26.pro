TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS += -lstdc++fs

INCLUDEPATH += "/usr/include/SDL2/"

HEADERS +=  \
  application.hpp \
  firestream.hpp \
  game.hpp \
  menu.hpp \
  menuSettings.hpp \
  sdlengine.hpp \
  settings.hpp \
  strResources.hpp \
  texture.hpp \
  texturetext.hpp \
  timer.hpp

SOURCES +=  \
  application.cpp \
  firestream.cpp \
  game.cpp \
  main.cpp \
  menu.cpp \
  menuSettings.cpp \
  sdlengine.cpp \
  settings.cpp \
  strResources.cpp \
  texture.cpp \
  texturetext.cpp \
  timer.cpp

DISTFILES += \
  settings.stg
