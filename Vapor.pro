QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/SearchItemVisitor.cpp \
    model/Soundtrack.cpp \
    model/DLC.cpp \
    model/Videogame.cpp \
    main.cpp \
    model/AbstractItem.cpp \
    model/Software.cpp \
    view/MainWindow.cpp

HEADERS += \    #controllare spesso che ci siano tutti
    model/SearchItemVisitor.h \
    model/Soundtrack.h \
    model/DLC.h \
    model/Videogame.h \
    model/AbstractItem.h \
    model/IConstVisitor.h \
    model/IVisitor.h \
    model/Software.h \
    view/MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
