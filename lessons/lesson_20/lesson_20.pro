TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += "/usr/include/SDL2/"

SOURCES += \
        application.cpp \
        ball.cpp \
        block.cpp \
        game.cpp \
        main.cpp \
        menu.cpp \
        menuSettings.cpp \
        sdlengine.cpp \
        settings.cpp \
        strResources.cpp \
        texturetext.cpp \
        timer.cpp


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS += -lstdc++fs

DISTFILES += \
  settings.stg

HEADERS += \
  application.hpp \
  ball.hpp \
  block.hpp \
  game.hpp \
  menu.hpp \
  menuSettings.hpp \
  sdlengine.hpp \
  settings.hpp \
  strResources.hpp \
  texturetext.hpp \
  timer.hpp
