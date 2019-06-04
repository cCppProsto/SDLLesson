TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ltexture.cpp \
        main.cpp


LIBS += -lSDL2 -lSDL2_image

HEADERS += \
  ltexture.hpp
