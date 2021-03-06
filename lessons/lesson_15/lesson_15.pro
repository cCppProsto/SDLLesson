TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        texture.cpp


LIBS += -lSDL2 -lSDL2_image

HEADERS += \
  texture.hpp
