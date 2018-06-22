
cmake_minimum_required(VERSION 2.8)

#PROJECT(MT_TOOLS)

#set(MT_TOOLS
#    Time_Series_Tools

#    )

add_executable(Exchangecomp Time_Series_Tools/Exchangecomp.cpp)
add_executable(Magmean Time_Series_Tools/Magmean.cpp)
add_executable(Mtu2birrp Time_Series_Tools/Mtu2birrp.cpp)
add_executable(Mtubandpass Time_Series_Tools/Mtubandpass.cpp)
add_executable(Mtucross Time_Series_Tools/Mtucross.cpp)
add_executable(Mtucut Time_Series_Tools/Mtucut.cpp)
add_executable(Mtufdiff Time_Series_Tools/Mtufdiff.cpp)
add_executable(Mtumerge Time_Series_Tools/Mtumerge.cpp)
add_executable(Mtuparms Time_Series_Tools/Mtuparms.cpp)
add_executable(Mtupspec Time_Series_Tools/Mtupspec.cpp)
add_executable(Mtura Time_Series_Tools/Mtura.cpp)
add_executable(Rotts Time_Series_Tools/Rotts.cpp)
add_executable(Syncts Time_Series_Tools/Syncts.cpp)
#add_executable(generatemtts Time_Series_Tools/generatemtts.cpp)
add_executable(mtugood Time_Series_Tools/mtugood.cpp)
add_executable(mtupca Time_Series_Tools/mtupca.cpp)
#add_executable(mtutimefrequency Time_Series_Tools/mtutimefrequency.cpp)

add_executable(Mtucorr Time_Series_Noise_Removal/Mtucorr.cpp)
add_executable(Mtumedian Time_Series_Noise_Removal/Mtumedian.cpp)
add_executable(DelayFilter Time_Series_Noise_Removal/DelayFilter.cpp)
#add_executable(mtunn Time_Series_Noise_Removal/mtunn.cpp)
#add_executable(mtuadaptive Time_Series_Noise_Removal/mtuadaptive.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/MT_Tools)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin/MT_Tools)

#aux_source_directory (Time_Series_Tools Time_Series_Tools_List)
#foreach (MT_Tools ${Time_Series_Tools_List})
#    add_executable(Time_Series_Tools_List {Time_Series_Tools_List})
#endforeach()

add_definitions(-D__STDC_FORMAT_MACROS)
set_property(DIRECTORY PROPERTY COMPILE_OPTIONS ${EXTRA_CXX_FLAGS})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(parsebyparts pthread)
endif()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})
