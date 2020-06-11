TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

#Отключить "теневую сборку" в криейторе!
CONFIG(release, debug|release) {

message(Project $$TARGET (Release))

OBJECTS_DIR = build/release
MOC_DIR = build/release
RCC_DIR = build/release
UI_DIR = build/release
}
CONFIG(debug, debug|release) {

message(Project $$TARGET (Debug))

OBJECTS_DIR = build/debug
MOC_DIR = build/debug
RCC_DIR = build/debug
UI_DIR = build/debug
DEFINES += DEBUG_BUILD
}

SOURCES += \
        UtilsTest.cpp

# Доп. файлы для тестирования
INCLUDEPATH += ../../include
HEADERS += \
    ../../include/Utils.h

SOURCES += \
    ../../src/Utils.cpp

# Boost
LIBS += -L/usr/lib/x86_64-linux-gnu \
        -lboost_filesystem \
        -lboost_system \
        -lboost_unit_test_framework \
