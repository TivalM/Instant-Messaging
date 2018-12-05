#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T10:09:15
#
#-------------------------------------------------

QT       += core gui
QT += websockets
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
    components/BaseWindow.cpp \
    components/ChatForm.cpp \
    components/ListItemForm.cpp \
    components/TitleBar.cpp \
    pages/ContactForm.cpp \
    pages/LoginDialog.cpp \
    pages/MainDialog.cpp \
    pages/RegisterDialog.cpp \
    pages/SessionForm.cpp \
    pages/ToolsForm.cpp \
    ClientCore.cpp \
    main.cpp \
    MainSystem.cpp \
    Message.cpp \
    Session.cpp \
    User.cpp \
    components/BaseWindow.cpp \
    components/ChatForm.cpp \
    components/ListItemForm.cpp \
    components/TitleBar.cpp \
    pages/ContactForm.cpp \
    pages/LoginDialog.cpp \
    pages/MainDialog.cpp \
    pages/RegisterDialog.cpp \
    pages/SessionForm.cpp \
    pages/ToolsForm.cpp \
    ClientCore.cpp \
    main.cpp \
    MainSystem.cpp \
    Message.cpp \
    Session.cpp \
    User.cpp \
    pages/PersonInfoForm.cpp


HEADERS += \
    components/BaseWindow.h \
    components/ChatForm.h \
    components/ListItemForm.h \
    components/TitleBar.h \
    pages/ContactForm.h \
    pages/LoginDialog.h \
    pages/MainDialog.h \
    pages/PersonInfoForm.h \
    pages/RegisterDialog.h \
    pages/SessionForm.h \
    pages/ToolsForm.h \
    ClientCore.h \
    MainSystem.h \
    Message.h \
    Session.h \
    User.h \
    components/BaseWindow.h \
    components/ChatForm.h \
    components/ListItemForm.h \
    components/TitleBar.h \
    pages/ContactForm.h \
    pages/LoginDialog.h \
    pages/MainDialog.h \
    pages/PersonInfoForm.h \
    pages/RegisterDialog.h \
    pages/SessionForm.h \
    pages/ToolsForm.h \
    ClientCore.h \
    MainSystem.h \
    Message.h \
    Session.h \
    User.h


FORMS += \
    components/CharHeadForm.ui \
    components/ChatForm.ui \
    components/FunctionTitleBar.ui \
    components/ListItemForm.ui \
    pages/LoginDialog.ui \
    pages/MainDialog.ui \
    pages/PersonInfoForm.ui \
    pages/RegisterDialog.ui \
    pages/SessionForm.ui \
    pages/ToolsForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc \
    src.qrc

SUBDIRS += \
    InstantMessage.pro

DISTFILES += \
    image/add.png \
    image/confirm.png \
    image/down.png \
    image/emoji.png \
    image/file.png \
    image/friend.png \
    image/head.png \
    image/head2.png \
    image/head3.png \
    image/head4.png \
    image/head5.png \
    image/head6.png \
    image/head7.png \
    image/head8.png \
    image/history.png \
    image/img.png \
    image/lock.png \
    image/login_background.png \
    image/mail.png \
    image/max.png \
    image/more.png \
    image/peerInfo.png \
    image/recording.png \
    image/restore.png \
    image/ring.png \
    image/send.png \
    image/tool.png \
    image/up.png \
    image/user.png \
    image/头像1_u110.png \
    image/chat.svg \
    image/close.svg \
    image/min.svg \
    css/BarButton.css \
    css/SessionForm.css
