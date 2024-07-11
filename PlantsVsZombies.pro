QT       += core gui network multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    Authorization.cpp \
    Menu.cpp \
    bullet.cpp \
    changeaccountinformation.cpp \
    client.cpp \
    emoji.cpp \
    forgotpassword.cpp \
    letsplay.cpp \
    main.cpp \
    mouse.cpp \
    plant.cpp \
    plantcard.cpp \
    plantgame.cpp \
    resource.cpp \
    server.cpp \
    showhistory.cpp \
    signupdialog.cpp \
    start.cpp \
    zombie.cpp \
    zombiecard.cpp \
    zombiegame.cpp

HEADERS += \
    Authorization.h \
    Menu.h \
    bullet.h \
    changeaccountinformation.h \
    client.h \
    emoji.h \
    forgotpassword.h \
    letsplay.h \
    mouse.h \
    plant.h \
    plantcard.h \
    plantgame.h \
    resource.h \
    server.h \
    showhistory.h \
    signupdialog.h \
    start.h \
    zombie.h \
    zombiecard.h \
    zombiegame.h

FORMS += \
    Authorization.ui \
    Menu.ui \
    changeaccountinformation.ui \
    forgotpassword.ui \
    letsplay.ui \
    showhistory.ui \
    signupdialog.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc \
    background.qrc \
    bg.qrc \
    loginbg.qrc \
    menu.qrc
