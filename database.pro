TEMPLATE = app
CONFIG += c++20
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/bin/

#Отключить "теневую сборку" в криейторе!
CONFIG(release, debug|release)
{
    message(Project $$TARGET (Release))

    OBJECTS_DIR = build/
    MOC_DIR = build/
    RCC_DIR = build/
    UI_DIR = build/
}
CONFIG(debug, debug|release)
{
    message(Project $$TARGET (Debug))

    OBJECTS_DIR = build/
    MOC_DIR = build/
    RCC_DIR = build/
    UI_DIR = build/
    DEFINES += DEBUG_BUILD

    # Boost
    LIBS += -L/usr/lib/x86_64-linux-gnu \
    -lboost_filesystem \
    -lboost_system \
    -lboost_program_options \
    -lboost_regex \
    -lpthread
}

macx
{
    INCLUDEPATH = /opt/homebrew/include
    COMMON_LIBS_DIR = /opt/homebrew/lib

    # Boost
    LIBS += -L$$COMMON_LIBS_DIR \
            -lboost_filesystem \
            -lboost_system \
            -lboost_program_options \
            -lboost_regex \
            -lpthread
}

INCLUDEPATH += include/
HEADERS += \
    include/AbstractFactory.h \
    include/Accountant.h \
    include/Cashier.h \
    include/ChiefAccountant.h \
    include/ChiefLegalCounsel.h \
    include/Data.h \
    include/Director.h \
    include/Driver.h \
    include/Employee.h \
    include/HeadOfProcurement.h \
    include/HeadOfWarehouse.h \
    include/HRManager.h \
    include/IEmployee.h \
    include/Lawyer.h \
    include/Loader.h \
    include/Logger.h \
    include/Logistician.h \
    include/PurchasingManager.h \
    include/SalesManager.h \
    include/tinyxml2.h \
    include/Utils.h

SOURCES += \
    src/Accountant.cpp \
    src/AccountantCreator.cpp \
    src/Cashier.cpp \
    src/CashierCreator.cpp \
    src/ChiefAccountant.cpp \
    src/ChiefAccountantCreator.cpp \
    src/ChiefLegalCounsel.cpp \
    src/ChiefLegalCounselCreator.cpp \
    src/Data.cpp \
    src/Director.cpp \
    src/DirectorCreator.cpp \
    src/Driver.cpp \
    src/DriverCreator.cpp \
    src/Employee.cpp \
    src/HeadOfProcurement.cpp \
    src/HeadOfProcurementCreator.cpp \
    src/HeadOfWarehouse.cpp \
    src/HeadOfWarehouseCreator.cpp \
    src/HRManager.cpp \
    src/HRManagerCreator.cpp \
    src/Lawyer.cpp \
    src/LawyerCreator.cpp \
    src/Loader.cpp \
    src/LoaderCreator.cpp \
    src/Logger.cpp \
    src/Logistician.cpp \
    src/LogisticianCreator.cpp \
    src/main.cpp \
    src/PurchasingManager.cpp \
    src/PurchasingManagerCreator.cpp \
    src/SalesManager.cpp \
    src/SalesManagerCreator.cpp \
    src/tinyxml2.cpp \
    src/Utils.cpp


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
