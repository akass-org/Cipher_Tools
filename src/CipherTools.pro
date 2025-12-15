QT       += core gui network
TARGET = CipherTools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 #static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    About.cpp \
    Home.cpp \
    main.cpp \
    settings.cpp \
    tools/deviceinfo.cpp \
    tools/multiout.cpp \
    tools/wakenow.cpp

HEADERS += \
    About.h \
    Home.h \
    settings.h \
    tools/deviceinfo.h \
    tools/multiout.h \
    tools/wakenow.h \
    version.h

FORMS += \
    About.ui \
    Home.ui \
    settings.ui \
    tools/deviceinfo.ui \
    tools/multiout.ui \
    tools/wakenow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
