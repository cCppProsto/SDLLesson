TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        goblinSurface.cpp \
        main.cpp \
        renderer.cpp

HEADERS += \
  goblinSurface.hpp \
  renderer.hpp


LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
