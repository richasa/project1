QT += core
QT -= gui

TARGET = oppgave1b
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += C:\Qt\include

# LIBS += -L C:\Qt
LIBS += -lliblapack -llibblas
TEMPLATE = app

SOURCES += main.cpp

HEADERS +=

