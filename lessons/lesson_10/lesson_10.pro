TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ltexture.cpp \
        main.cpp


HEADERS += \
  ltexture.hpp

LIBS += -lSDL2 -lSDL2_image
