TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        texture.cpp

HEADERS += \
  texture.hpp

LIBS += -lSDL2 -lSDL2_image
