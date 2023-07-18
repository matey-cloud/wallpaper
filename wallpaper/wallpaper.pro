QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datamanager.cpp \
    imagedatainfo.cpp \
    imageinfoitem.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    datamanager.h \
    imagedatainfo.h \
    imageinfoitem.h \
    mainwindow.h

FORMS += \
    imageinfoitem.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/title.png \
    img/close.ico \
    img/min.ico \
    img/title.ico \
    img/title/title.ico \
    qss/scrollbar.qss

RESOURCES += \
    resources.qrc

LIBS += -lUser32
