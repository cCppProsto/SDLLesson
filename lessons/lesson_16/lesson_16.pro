TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        texturesprite.cpp \
        texturetext.cpp

HEADERS += \
  texturesprite.hpp \
  texturetext.hpp


LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf
