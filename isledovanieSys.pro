TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = qt-libxl

SOURCES += main.cpp \
    methods.cpp \


win32 {

    INCLUDEPATH = D:/Work/GitHubProjects/islMethods/isledovanieSys/headers
    LIBS += D:/Work/GitHubProjects/islMethods/isledovanieSys/libs/libxl.dll

    QMAKE_POST_LINK +=$$quote(cmd /c copy /y D:\Work\GitHubProjects\islMethods\isledovanieSys\libs\libxl.dll)

}
