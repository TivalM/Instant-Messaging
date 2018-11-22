#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T10:09:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InstantMessage
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        LoginDialog.cpp \
    TitleBar.cpp \
    BaseWindow.cpp \
    RegisterDialog.cpp \
    MainDialog.cpp \
    SessionForm.cpp \
    PerPersonForm.cpp \
    User.cpp \
    Message.cpp \
    MainSystem.cpp

HEADERS += \
        LoginDialog.h \
    TitleBar.h \
    BaseWindow.h \
    RegisterDialog.h \
    MainDialog.h \
    SessionForm.h \
    PerPersonForm.h \
    User.h \
    Message.h \
    MainSystem.h

FORMS += \
        LoginDialog.ui \
    RegisterDialog.ui \
    MainDialog.ui \
    SessionForm.ui \
    PerPersonForm.ui \
    FunctionTitleBar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
