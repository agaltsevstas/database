TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        UtilsTest.cpp

# modules for testing
INCLUDEPATH += ../../include
HEADERS += \
    ../../include/Utils.h

SOURCES += \
    ../../src/Utils.cpp
