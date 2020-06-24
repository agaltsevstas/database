TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/bin/

#Отключить "теневую сборку" в криейторе!
CONFIG(release, debug|release) {

message(Project $$TARGET (Release))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
}
CONFIG(debug, debug|release) {

message(Project $$TARGET (Debug))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
DEFINES += DEBUG_BUILD
}

INCLUDEPATH += include/ука
HEADERS += \
    include/SalesManager.h \
    include/TradingCompany.h \
    include/Utils.h \
    include/Accountant.h \
    include/Cashier.h \
    include/ChiefAccountant.h \
    include/ChiefLegalCounsel.h \
    include/Data.h \
    include/Director.h \
    include/Driver.h \
    include/HeadOfProcurement.h \
    include/HeadOfWarehouse.h \
    include/Hrmanager.h \
    include/Lawyer.h \
    include/Loader.h \
    include/Logger.h \
    include/Logistician.h \
    include/PurchasingManager.h \
    include/tinyxml2.h

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
    src/HRManager.cpp \
    src/Lawyer.cpp \
    src/Loader.cpp \
    src/Logger.cpp \
    src/Logistician.cpp \
    src/PurchasingManager.cpp \
    src/SalesManager.cpp \
    src/TradingCompany.cpp \
    src/main.cpp \
    src/Utils.cpp \
    src/tinyxml2.cpp

# Boost and common
LIBS += -L/usr/lib/аукаx86_64-linux-gnu \
        -lboost_filesystem \
        -lboost_system \
        -lboost_program_options \
        -lboost_regex \
        -lpthread

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
