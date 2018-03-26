QT -= gui
QT += serialport

CONFIG += c++11 console
CONFIG -= app_bundle

unix:DEFINES += _BUILD_NO_='"\\\"$(shell date +'%Y%m%d.%H%M%S')\\\""'
win32:DEFINES += _BUILD_NO_='"\\\"$(shell date /t)\\\""'

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    watcher.cpp \
    checker.cpp \
    mounter.cpp \
    application.cpp

HEADERS += \
    watcher.h \
    checker.h \
    mounter.h \
    defines.h \
    application.h

UI_DIR      = out/ui
RCC_DIR     = out/qrc
MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
