QT       += core gui
QT+= network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createchannel.cpp \
    date.cpp \
    joinchannel.cpp \
    joingroup.cpp \
    login.cpp \
    logout.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    myfile.cpp \
    request.cpp \
    sendmessageuser.cpp \
    signup.cpp \
    user.cpp
    message.cpp

HEADERS += \
    createchannel.h \
    date.h \
    joinchannel.h \
    joingroup.h \
    login.h \
    logout.h \
    mainwindow.h \
    message.h \
    myfile.h \
    request.h \
    sendmessageuser.h \
    signup.h \
    user.h
    message.h

FORMS += \
    createchannel.ui \
    joinchannel.ui \
    joingroup.ui \
    login.ui \
    logout.ui \
    mainwindow.ui \
    sendmessageuser.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc

DISTFILES +=
