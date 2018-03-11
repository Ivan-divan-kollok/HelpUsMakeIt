#-------------------------------------------------
#
# Project created by QtCreator 2018-02-21T14:11:39
#
#-------------------------------------------------

QT       += core gui serialport testlib
CONFIG   += c++11 warn_on

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

QT.testlib.CONFIG -= console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

QMAKE_CFLAGS_RELEASE += -O2
QMAKE_CFLAGS += -Wall -Wextra -Wfloat-equal -Wundef -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wshadow -Wdiv-by-zero
QMAKE_CFLAGS += -isystem $$[QT_INSTALL_HEADERS]

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -Wundef -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wshadow -Wdiv-by-zero
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

SOURCES += main.cpp \
        mainwindow.cpp \
    ../ANGEL/Equipment/CommonFunctionsForSRS/SRS.cpp \
    ../ANGEL/Equipment/LockInAmplifier/LockInAmplifier/LockInAmplifier.cpp \
    ../ANGEL/Equipment/LockInAmplifier/SR830/SR830.cpp \
    ../ANGEL/Equipment/LockInAmplifier/SR844/SR844.cpp \
    ../ANGEL/Equipment/LockInAmplifier/SR865/SR865.cpp \
    ../ANGEL/Functions/AllFunctions.cpp

HEADERS += mainwindow.h \
    ../ANGEL/Equipment/CommonFunctionsForSRS/SRS.h \
    ../ANGEL/Equipment/LockInAmplifier/LockInAmplifier/LockInAmplifier.h \
    ../ANGEL/Equipment/LockInAmplifier/SR830/SR830.h \
    ../ANGEL/Equipment/LockInAmplifier/SR844/SR844.h \
    ../ANGEL/Equipment/LockInAmplifier/SR865/SR865.h \
    ../ANGEL/Equipment/LockInAmplifier/AllLockInAmplifiers.h \
    ../ANGEL/Equipment/AllEquipment.h \
    ../ANGEL/Functions/AllFunctions.h \
    ../ANGEL/Angel.h

FORMS += mainwindow.ui
