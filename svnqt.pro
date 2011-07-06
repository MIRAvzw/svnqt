include(src/svnqt.pri)

TEMPLATE = lib
QT += core sql
TARGET = svnqt

VERSION = 1.6.0

DEPENDPATH += src
INCLUDEPATH += src /usr/include/subversion-1 /usr/include/apr-1

DEFINES += SVNQT_LIBRARY

