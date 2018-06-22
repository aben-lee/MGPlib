######################################################################
# Generic Library
######################################################################

BASE_DIR = $$PWD/../
#!isEmpty(ROOT_DIR): BASE_DIR = $$ROOT_DIR

#TEMPLATE = app
#CONFIG += static
#DLLDESTDIR = $$BASE_DIR/bin
#DESTDIR = $$BASE_DIR/bin

#CONFIG(debug, debug|release) {
#    TARGET = $$join(TARGET,,,d)
#}

DEPENDPATH     += . $${BASE_DIR}/include
INCLUDEPATH    += . $${BASE_DIR}/include

DEPENDPATH     += . $${BASE_DIR}/3rdparty/rapidjson/include
INCLUDEPATH    += . $${BASE_DIR}/3rdparty/rapidjson/include
##################################################################################

INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Exceptions
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Global
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Time_Series_Tools
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Statistics
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Signal_Processing
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Neural_Network
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/GAClasses
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Seismic_Tools
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/Joint_Inversion
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/Station_Parser
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/MT_Tensor_Tools
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/Time_Series_Tools
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/1DMT
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/EDI_Parser
INCLUDEPATH    += . $${BASE_DIR}/include/sdk/MT_Tools/J_Parser

########################################## boost Libaray #########################################

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_date_time-mgw53-1_62
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_date_time-mgw53-1_62d
else:unix: LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_date_time-mgw53-1_62

INCLUDEPATH += $$PWD/../3rdparty/boost_1_62_0
DEPENDPATH += $$PWD/../3rdparty/boost_1_62_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_date_time-mgw53-1_62.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_date_time-mgw53-1_62d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_date_time-mgw53-1_62.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_date_time-mgw53-1_62d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_date_time-mgw53-1_62.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_program_options-mgw53-1_62
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_program_options-mgw53-1_62d
else:unix: LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_program_options-mgw53-1_62

INCLUDEPATH += $$PWD/../3rdparty/boost_1_62_0
DEPENDPATH += $$PWD/../3rdparty/boost_1_62_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_program_options-mgw53-1_62.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_program_options-mgw53-1_62d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_program_options-mgw53-1_62.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_program_options-mgw53-1_62d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_program_options-mgw53-1_62.a

########################################## fftw Libaray #########################################


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/fftw-3.3.7/ -lfftw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/fftw-3.3.7/ -lfftw3d
else:unix: LIBS += -L$$PWD/../3rdparty/fftw-3.3.7/ -lfftw3

INCLUDEPATH += $$PWD/../3rdparty/fftw-3.3.7
DEPENDPATH += $$PWD/../3rdparty/fftw-3.3.7

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/fftw-3.3.7/libfftw3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/fftw-3.3.7/libfftw3d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/fftw-3.3.7/fftw3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/fftw-3.3.7/fftw3d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/fftw-3.3.7/libfftw3.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_filesystem-mgw53-1_62
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_filesystem-mgw53-1_62d
else:unix: LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_filesystem-mgw53-1_62

INCLUDEPATH += $$PWD/../3rdparty/boost_1_62_0
DEPENDPATH += $$PWD/../3rdparty/boost_1_62_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_filesystem-mgw53-1_62.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_filesystem-mgw53-1_62d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_filesystem-mgw53-1_62.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_filesystem-mgw53-1_62d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_filesystem-mgw53-1_62.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_system-mgw53-1_62
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_system-mgw53-1_62d
else:unix: LIBS += -L$$PWD/../3rdparty/boost_1_62_0/stage/lib/ -lboost_system-mgw53-1_62

INCLUDEPATH += $$PWD/../3rdparty/boost_1_62_0
DEPENDPATH += $$PWD/../3rdparty/boost_1_62_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_system-mgw53-1_62.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_system-mgw53-1_62d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_system-mgw53-1_62.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/boost_system-mgw53-1_62d.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/boost_1_62_0/stage/lib/libboost_system-mgw53-1_62.a



########################################## antlr-2.7.7 Libaray #########################################


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/antlr-2.7.7/lib/ -lantlr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/antlr-2.7.7/lib/ -lantlrd
else:unix: LIBS += -L$$PWD/../3rdparty/antlr-2.7.7/lib/ -lantlr

INCLUDEPATH += $$PWD/../3rdparty/antlr-2.7.7
DEPENDPATH += $$PWD/../3rdparty/antlr-2.7.7

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/antlr-2.7.7/lib/libantlr.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/antlr-2.7.7/lib/libantlrd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/antlr-2.7.7/lib/antlr.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/antlr-2.7.7/lib/antlrd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3rdparty/antlr-2.7.7/lib/libantlr.a

