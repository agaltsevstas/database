TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_PROJECT_DEPTH = 0

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

INCLUDEPATH += include/
HEADERS += \
    include/Accountant.h \
    include/Cashier.h \
    include/ChiefAccountant.h \
    include/ChiefLegalCounsel.h \
    include/Data.h \
    include/Director.h \
    include/Driver.h \
    include/HeadOfProcurement.h \
    include/HeadOfWarehouse.h \
    include/Lawyer.h \
    include/Loader.h \
    include/Logger.h \
    include/Logistician.h \
    include/PurchasingManager.h \
    include/SalesManager.h \
    include/TradingCompany.h \
    include/Utils.h

SOURCES += \
    src/Accountant.cpp \
    src/Cashier.cpp \
    src/ChiefAccountant.cpp \
    src/ChiefLegalCounsel.cpp \
    src/Data.cpp \
    src/Director.cpp \
    src/Driver.cpp \
    src/HeadOfProcurement.cpp \
    src/HeadOfWarehouse.cpp \
    src/Lawyer.cpp \
    src/Loader.cpp \
    src/Logger.cpp \
    src/Logistician.cpp \
    src/PurchasingManager.cpp \
    src/SalesManager.cpp \
    src/TradingCompany.cpp \
    src/main.cpp \
    src/Utils.cpp

# Boost and common
LIBS += -L/usr/lib/x86_64-linux-gnu \
        -lboost_filesystem \
        -lboost_system \
        -lboost_program_options \
        -lboost_log \
        -lboost_log_setup \
        -lboost_thread \
        -lboost_regex \
        -lboost_unit_test_framework \
        -lpthread \
        -ldl -fPIC

DISTFILES += \
    data/accountant.txt \
    data/cashier.txt \
    data/chief_accountant.txt \
    data/chief_legal_counsel.txt \
    data/director.txt \
    data/driver.txt \
    data/head_of_procurement.txt \
    data/head_of_warehouse.txt \
    data/lawyer.txt \
    data/logistician.txt \
    data/purchasing_manager.txt \
    data/sales_manager.txt \
    data/stevedore.txt
