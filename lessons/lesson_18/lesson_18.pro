TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        application.cpp \
        main.cpp \
        menu.cpp \
        menuSettings.cpp \
        sdlengine.cpp \
        settings.cpp \
        texturetext.cpp

HEADERS += \
  application.hpp \
  menu.hpp \
  menuSettings.hpp \
  sdlengine.hpp \
  settings.hpp \
  texturetext.hpp


LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
