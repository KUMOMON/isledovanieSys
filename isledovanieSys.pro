TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

TARGET = qt-libxl

INCLUDEPATH+= headers


SOURCES += main.cpp \
    methods.cpp \

win32 {

    INCLUDEPATH = headers
    LIBS += libs/libxl.lib

    QMAKE_POST_LINK +=$$quote(cmd /c copy /y ..\..\..\bin\libxl.dll .)

}
