######################################################################
# gplib++ qmake files
######################################################################
BASE_DIR = $$PWD/../
!isEmpty(ROOT_DIR): BASE_DIR = $$ROOT_DIR

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#DLLDESTDIR = $$BASE_DIR/bin
DESTDIR = $$BASE_DIR/bin

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}

include( $$PWD/MT_Tools.pri )

DEFINES += HAVEANTLR

# Input

SOURCES +=Time_Series_Tools/Finish/mtubandpass.cpp
TARGET = mtubandpass

#SOURCES += ptensor/phasetensormap.cpp
#TARGET = phasetensormap

#SOURCES += \
#    Time_Series_Tools\Finish\Mtumerge.cpp
#TARGET = Mtumerge
