#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T19:12:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = behavioral-tree-editor
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    NewNodeDialog.cpp \
    NodeTypes.cpp \
    Serializer.cpp \
    Tree.cpp

HEADERS  += MainWindow.hpp \
    NewNodeDialog.hpp \
    NodeTypes.hpp \
    Serializer.hpp \
    Tree.hpp

FORMS    += MainWindow.ui \
    NewNodeDialog.ui
