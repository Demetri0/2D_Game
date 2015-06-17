#-------------------------------------------------
#
# Project created by QtCreator 2013-12-30T17:49:22
#
#-------------------------------------------------

#QT       += core

QT       -= gui # core

LIBS += -lGL -lGLU -lglut -lopenal -lalut

TARGET = Mario
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tile.cpp \
    rect.cpp \
    unit.cpp \
    map.cpp \
    openal.cpp

HEADERS += \
    tile.h \
    rect.h \
    unit.h \
    map.h \
    LoadTGA.h \
    openal.h
