QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeaccountinformation.cpp \
    client.cpp \
    forgotpassword.cpp \
    main.cpp \
    plants.cpp \
    plantslogin.cpp \
    plantsmenu.cpp \
    server.cpp \
    showhistory.cpp \
    signupdialog.cpp \
    zombies.cpp \
    zombieslogin.cpp \
    zombiesmenu.cpp

HEADERS += \
    changeaccountinformation.h \
    client.h \
    forgotpassword.h \
    plants.h \
    plantslogin.h \
    plantsmenu.h \
    server.h \
    showhistory.h \
    signupdialog.h \
    zombies.h \
    zombieslogin.h \
    zombiesmenu.h

FORMS += \
    changeaccountinformation.ui \
    forgotpassword.ui \
    plants.ui \
    plantslogin.ui \
    plantsmenu.ui \
    showhistory.ui \
    signupdialog.ui \
    zombies.ui \
    zombieslogin.ui \
    zombiesmenu.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
