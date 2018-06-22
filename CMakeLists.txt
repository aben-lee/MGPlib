########################################################################
# cmake file for MGpLib project association
# author: Xiaobin Li
# created: June 14, 2018
########################################################################

cmake_minimum_required(VERSION 2.8)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

include_directories("include")

set(MAJOR_VERSION "1")
set(MINOR_VERSION "0")
set(PATCH_VERSION "0")
set(VERSION_STRING "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)


################################################################################
# Make sure you have the following libraries installed compiler. The defaults relative
# paths is 3rdparty path of the project, Under linux you might be able to install them
# as part of your distribution, then you just change the set(**_HOME XXXX) of associated
# library.

# add 1.55 or later library
set(Boost_HOME 3rdparty/boost_1_62_0)  # please change the boost_1_62_0 path according to its location

include_directories(${Boost_HOME})
FIND_LIBRARY(BOOST_FILESYSTEM_LIB libboost_filesystem-mgw53-1_62 ${Boost_HOME}/stage/lib NO_DEFAULT_PATH)
FIND_LIBRARY(BOOST_DATE_TIME_LIB libboost_date_time-mgw53-1_62 ${Boost_HOME}/stage/lib NO_DEFAULT_PATH)
FIND_LIBRARY(BOOST_program_options_LIB libboost_program_options-mgw53-1_62 ${Boost_HOME}/stage/lib NO_DEFAULT_PATH)
FIND_LIBRARY(BOOST_system_LIB libboost_system-mgw53-1_62 ${Boost_HOME}/stage/lib NO_DEFAULT_PATH)
FIND_LIBRARY(BOOST_system_LIB libboost_system-mgw53-1_62 ${Boost_HOME}/stage/lib NO_DEFAULT_PATH)
link_directories(${Boost_HOME}/stage/lib)
link_libraries(${BOOST_FILESYSTEM_LIB} ${BOOST_DATE_TIME_LIB} ${BOOST_program_options_LIB} ${BOOST_system_LIB})

# add rapidjson 1.1.0 or later library
set(Rapidjson_HOME 3rdparty/rapidjson)  # please change the rapidjson path according to its location
include_directories(${Rapidjson_HOME}/include)

# add FFTW3 library
set(FFTW3_HOME 3rdparty/fftw-3.3.8)   # please change the fftw-3.3.7 path according to its location
include_directories(${FFTW3_HOME}/api)
FIND_LIBRARY(FFTW3_LIB libfftw3 ${FFTW3_HOME}/lib NO_DEFAULT_PATH)
link_libraries(${FFTW3_LIB})

################################################################################
# The following libraries are optional. Ideally the build system should tell you that these
# extensions are disabled if you don't have them, but build everything else.

set(antlr_home 3rdparty/antlr-2.7.7)  # please change the antlr path according to its location
set(netcdf_home 3rdparty/netcdf-cxx-4.2)  # please change the antlr path according to its location
option(MGPLIB_BUILD_ANTLR "Build antlr-2.7.7 libraries." ON)
option(MGPLIB_BUILD_NETCDF "Build netcdf-4.2 libraries." ON)
option(MGPLIB_BUILD_DOC "Build MGpLib documentation." ON)
option(MGPLIB_BUILD_EXAMPLES "Build MGpLib examples." OFF)
option(MGPLIB_BUILD_TESTS "Build MGpLib unittests." OFF)
option(MGPLIB_BUILD_THIRDPARTY_GTEST
    "Use gtest installation in `3rdparty/gtest` by default if available" OFF)

option(MGPLIB_BUILD_CXX11 "Build MGpLib with C++11 (gcc/clang)" ON)


# =================== the following should not change any more ====================================

if(MGPLIB_BUILD_ANTLR)
    include_directories(${antlr_home})
    find_library(ANTLR_LIB libantlr ${antlr_home}/lib NO_DEFAULT_PATH)
    link_directories(${antlr_home}/lib)
    link_libraries(${ANTLR_LIB})
endif()

if(MGPLIB_BUILD_NETCDF)
    include_directories(${netcdf_home}/cxx)
#    find_library(ANTLR_LIB libantlr ${netcdf_home}/lib NO_DEFAULT_PATH)
#    link_directories(${antlr_home}/lib)
#    link_libraries(${ANTLR_LIB})
endif()

if(MGPLIB_BUILD_DOC)
    add_subdirectory(doc)
endif()

if(MGPLIB_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

if(MGPLIB_BUILD_TESTS)
    if(MSVC11)
        # required for VS2012 due to missing support for variadic templates
        add_definitions(-D_VARIADIC_MAX=10)
    endif(MSVC11)
    add_subdirectory(test)
    include(CTest)
endif()

################################################################################

set(CUSTOM_HEAD_DIR include)

#file(GLOB_RECURSE HEADER_FILES ../../include/*.h??)

#foreach (heads ${HEADER_FILES})
#    include(${heads})
#endforeach()

include_directories(${CUSTOM_HEAD_DIR}/sdk/Global)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Time_Series_Tools)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Statistics)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Signal_Processing)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Neural_Network)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Exceptions)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Neural_Network)
include_directories(${CUSTOM_HEAD_DIR}/sdk/GAClasses)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Seismic_Tools)
include_directories(${CUSTOM_HEAD_DIR}/sdk/Joint_Inversion)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/Station_Parser)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/MT_Tensor_Tools)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/Time_Series_Tools)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/1DMT)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/EDI_Parser)
include_directories(${CUSTOM_HEAD_DIR}/sdk/MT_Tools/J_Parser)


add_subdirectory(src)

################################################################################
# Export package for use from the build tree
EXPORT( PACKAGE ${PROJECT_NAME} )

#set(BIN_DIR bin)  # please change the rapidjson path according to its location

# Create the MGpLibConfig.cmake file for other cmake projects.
# ... for the build tree
SET( CONFIG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET( CONFIG_DIR ${CMAKE_CURRENT_BINARY_DIR})
SET( ${PROJECT_NAME}_INCLUDE_DIR "\${${PROJECT_NAME}_SOURCE_DIR}/include" )

#CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake @ONLY )
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}ConfigVersion.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake @ONLY)

## ... for the install tree
#SET( CMAKECONFIG_INSTALL_DIR lib/cmake/${PROJECT_NAME} )
#FILE( RELATIVE_PATH REL_INCLUDE_DIR
#    "${CMAKE_INSTALL_PREFIX}/${CMAKECONFIG_INSTALL_DIR}"
#    "${CMAKE_INSTALL_PREFIX}/include" )

#SET( ${PROJECT_NAME}_INCLUDE_DIR "\${${PROJECT_NAME}_CMAKE_DIR}/${REL_INCLUDE_DIR}" )
#SET( CONFIG_SOURCE_DIR )
#SET( CONFIG_DIR )
#CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake @ONLY )

#INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake"
#        DESTINATION ${CMAKECONFIG_INSTALL_DIR} )

## Install files
#INSTALL(FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#    DESTINATION "${CMAKE_INSTALL_DIR}"
#    COMPONENT dev)


#INSTALL(TARGETS MGpLib MGpLib MGpLib
#       RUNTIME DESTINATION bin
#       LIBRARY DESTINATION lib
#       ARCHIVE DESTINATION libstatic
#)
