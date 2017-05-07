#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T13:23:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Spaceship
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    battlesphere.cpp \
    iofile.cpp \
    defender.cpp \
    commandcentre.cpp \
    battlespherebuilder.cpp \
    gamedirector.cpp \
    star.cpp \
    alienbullet.cpp \
    alienbulletadapter.cpp \
    defenderbullet.cpp \
    sharedmedia.cpp \
    sharedmediafactory.cpp \
    alien.cpp \
    aliencomposite.cpp \
    alienboss.cpp

HEADERS  += \
    battlesphere.h \
    iofile.h \
    defender.h \
    commandcentre.h \
    bullet.h \
    battlespherebuilder.h \
    gamedirector.h \
    star.h \
    gameelement.h \
    alienbullet.h \
    alienbulletadapter.h \
    defenderbullet.h \
    downbullet.h \
    upbullet.h \
    sharedmedia.h \
    sharedmediafactory.h \
    alien.h \
    aliencomponent.h \
    aliencomposite.h \
    alienboss.h

RESOURCES += \
    resources.qrc

OTHER_FILES +=
