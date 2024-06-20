QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Countdown.cpp \
    analogclock.cpp \
    attach.cpp \
    background.cpp \
    date.cpp \
    dateform.cpp \
    desktopbk.cpp \
    event.cpp \
    eventshow.cpp \
    main.cpp \
    mainmzk.cpp \
    mainwindow.cpp \
    qdatemodify.cpp \
    tomatoclock.cpp \
    user.cpp

HEADERS += \
    Countdown.h \
    analogclock.h \
    attach.h \
    background.h \
    date.h \
    dateform.h \
    desktopbk.h \
    event.h \
    eventshow.h \
    mainmzk.h \
    mainwindow.h \
    qdatemodify.h \
    tomatoclock.h \
    user.h \
    weatherdata.h

FORMS += \
    Countdown.ui \
    analogclock.ui \
    attach.ui \
    background.ui \
    dateform.ui \
    eventshow.ui \
    mainmzk.ui \
    mainwindow.ui \
    qdatemodify.ui \
    tomatoclock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    ress.qrc
