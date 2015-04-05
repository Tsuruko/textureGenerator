#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T21:05:06
#
#-------------------------------------------------

QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+

CONFIG +=c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = textureGenerator
TEMPLATE = app

INCLUDEPATH += ./Includes


SOURCES += main.cpp\
        window.cpp \
    Source/Bitmap.cpp \
    Source/CellTexture.cpp \
    Source/CloudTexture.cpp \
    Source/Color.cpp \
    Source/MarbleTexture.cpp \
    Source/PerlinNoise.cpp \
    Source/Scene.cpp \
    Source/Vector3.cpp \
    Source/WoodTexture.cpp \
    Source/WorleyNoise.cpp

HEADERS  += window.h \
    Includes/Bitmap.h \
    Includes/CellTexture.h \
    Includes/CloudTexture.h \
    Includes/Color.h \
    Includes/Core.h \
    Includes/MarbleTexture.h \
    Includes/PerlinNoise.h \
    Includes/Scene.h \
    Includes/Texture.h \
    Includes/Vector3.h \
    Includes/WoodTexture.h \
    Includes/WorleyNoise.h

FORMS    += window.ui
