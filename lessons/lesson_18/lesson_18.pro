TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        sdlengine.cpp

HEADERS += \
  sdlengine.hpp


LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
