TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17


LIBS += -lGL -lGLU -lglut -lGLEW
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS += -lstdc++fs

INCLUDEPATH += "/usr/include/SDL2/"

HEADERS +=  \
  application.hpp \
  menuSettings.hpp \
  sdlengine.hpp \
  settings.hpp \
  timer.hpp

SOURCES +=  \
  application.cpp \
  main.cpp \
  menuSettings.cpp \
  sdlengine.cpp \
  settings.cpp \
  timer.cpp

DISTFILES += \
  settings.stg
