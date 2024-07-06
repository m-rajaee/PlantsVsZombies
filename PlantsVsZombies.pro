QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    Authorization.cpp \
    Menu.cpp \
    changeaccountinformation.cpp \
    client.cpp \
    forgotpassword.cpp \
    main.cpp \
    plants.cpp \
    server.cpp \
    showhistory.cpp \
    signupdialog.cpp \
    zombies.cpp

HEADERS += \
    Authorization.h \
    Menu.h \
    changeaccountinformation.h \
    client.h \
    forgotpassword.h \
    plants.h \
    server.h \
    showhistory.h \
    signupdialog.h \
    zombies.h

FORMS += \
    Authorization.ui \
    Menu.ui \
    changeaccountinformation.ui \
    forgotpassword.ui \
    plants.ui \
    showhistory.ui \
    signupdialog.ui \
    zombies.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
