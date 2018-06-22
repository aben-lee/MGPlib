######################################################################
# gplib++ qmake files
######################################################################
BASE_DIR = $$PWD/../
!isEmpty(ROOT_DIR): BASE_DIR = $$ROOT_DIR

TEMPLATE = app
#CONFIG += static
TARGET = mtuBandPass
DLLDESTDIR = $$BASE_DIR/bin
DESTDIR = $$BASE_DIR/bin

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}


#include( $$PWD/../Global.pri )
#include( $$PWD/../Time_Series_Tools.pri )
#include( $$PWD/../Statistics.pri )

include( $$PWD/MT_Tools.pri )
#include( $$PWD/mtuBandPass.pro )

#!isEmpty(COMMERCIAL_BUILD) {
#        !exists( $${PROJECT_BASE}/CommercialComponents/CommercialComponents.pro ) {
#                error( "Cannot find " $${PROJECT_BASE}"/CommercialComponents/CommercialComponents.pro");
#        }

#        SUBDIRS += CommercialComponents
#        message("Building GNU/GPL and Commercial components")
#}

SOURCES += \
#    Time_Series_Tools/mtubandpass.cpp



########################################## boost Libaray #########################################

unix|win32: LIBS += -llibboost_filesystem-vc140-mt-1_61

unix|win32: LIBS += -llibboost_program_options-vc140-mt-1_61

unix|win32: LIBS += -llibboost_date_time-vc140-mt-1_61

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_filesystem-vc140-mt-1_61
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_filesystem-vc140-mt-1_61d
else:unix: LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_filesystem-vc140-mt-1_61

INCLUDEPATH += $$PWD/../../../library/boost_1_61_0
DEPENDPATH += $$PWD/../../../library/boost_1_61_0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_date_time-vc140-mt-1_61
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_date_time-vc140-mt-1_61d
else:unix: LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_date_time-vc140-mt-1_61


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_program_options-vc140-mt-1_61
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_program_options-vc140-mt-1_61d
else:unix: LIBS += -L$$PWD/../../../library/boost_1_61_0/stage/lib/ -llibboost_program_options-vc140-mt-1_61



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/fftw-3.3.4-dll32/ -llibfftw3-3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/fftw-3.3.4-dll32/ -llibfftw3-3d
else:unix: LIBS += -L$$PWD/../../3rdparty/fftw-3.3.4-dll32/ -llibfftw3-3

INCLUDEPATH += $$PWD/../../3rdparty/fftw-3.3.4-dll32
DEPENDPATH += $$PWD/../../3rdparty/fftw-3.3.4-dll32

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../3rdparty/fftw-3.3.4-dll32/liblibfftw3-3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../3rdparty/fftw-3.3.4-dll32/liblibfftw3-3d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../3rdparty/fftw-3.3.4-dll32/libfftw3-3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../3rdparty/fftw-3.3.4-dll32/libfftw3-3d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../3rdparty/fftw-3.3.4-dll32/liblibfftw3-3.a
