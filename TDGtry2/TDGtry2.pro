#-------------------------------------------------
#
# Project created by QtCreator 2020-06-09T21:16:24
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TDGtry2
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    choicewindow.cpp \
    mybutton.cpp \
    tower.cpp \
    myobject.cpp \
    myobject2.cpp \
    enemy.cpp \
    heart.cpp \
    plistreader.cpp

HEADERS += \
        mainwindow.h \
    choicewindow.h \
    mybutton.h \
    tower.h \
    myobject.h \
    myobject2.h \
    enemy.h \
    heart.h \
    plistreader.h

FORMS += \
        mainwindow.ui


#下面不知道该不该加、怎么加
DISTFILES += \
    ../../Downloads/3.3.28 数据依赖 jc .docx \
    ../../Downloads/3619.txt

#RESOURCES += \
#    game.qrc

RESOURCES += \
    res.qrc
