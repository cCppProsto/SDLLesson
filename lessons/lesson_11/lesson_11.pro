TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        texturesprite.cpp

HEADERS += \
  texturesprite.hpp

LIBS += -lSDL2 -lSDL2_image
