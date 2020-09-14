#-------------------------------------------------
#
# Project created by QtCreator 2019-01-19T13:15:01
#
#-------------------------------------------------

QT       += core gui multimedia widgets

TARGET = TempoEX
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        player.cpp \
        projectile.cpp \
        fileparser.cpp \
        star.cpp \
        scrap.cpp \
        asteroid.cpp \
        soundcontroller.cpp \
        gamecontroller.cpp \
        ship.cpp \
        weapon.cpp \
        clickableqlabel.cpp

HEADERS += \
        mainwindow.h \
        player.h \
        view.h \
        projectile.h \
        fileparser.h \
        star.h \
        scrap.h \
        asteroid.h \
        soundcontroller.h \
        gamecontroller.h \
        ship.h \
        weapon.h \
        clickableqlabel.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.xml

RESOURCES += \
    ressources.qrc
