#-------------------------------------------------
#
# Project created by QtCreator 2019-03-21T16:27:46
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++1z
CONFIG += c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pharmacy_qt
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


SOURCES += \
main.cpp \
mainwindow.cpp \
medicament.cpp \
regular_medicament.cpp \
base_of_regular_customers.cpp \
application_for_medicament.cpp \
pharm_firm.cpp \
date.cpp \
model_generator.cpp \
dose.cpp \
med_in_order.cpp \
order.cpp \
medicament_warehouse.cpp \
regular_customer.cpp \
computer_manager.cpp \
string_helpers.cpp

HEADERS += \
mainwindow.h \
model_generator.h \
computer_manager.h \
medicament_warehouse.h \
medicament.h \
date.h \
pharm_firm.h \
application_for_medicament.h \
base_of_regular_customers.h \
regular_customer.h \
order.h \
regular_medicament.h \
med_in_order.h \
dose.h \
string_helpers.h

RESOURCES +=

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
