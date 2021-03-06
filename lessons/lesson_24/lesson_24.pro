TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        application.cpp \
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

INCLUDEPATH += "/usr/include/SDL2/"

QMAKE_CXXFLAGS += -std=c++17

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS += -lstdc++fs

DISTFILES += \
  settings.stg

HEADERS += \
  application.hpp \
  game.hpp \
  menu.hpp \
  menuSettings.hpp \
  sdlengine.hpp \
  settings.hpp \
  strResources.hpp \
  texture.hpp \
  texturetext.hpp \
  timer.hpp
