#####
# Build Source of MGplib.
#####

option(BUILD_MT_TOOLS "Build MGplib MT Tools." ON)
#option(MGPLIB_BUILD_MT_TOOLS "Build rapidjson examples." ON)

if(BUILD_MT_TOOLS)
   add_subdirectory(MT_Tools)
endif()

# Build all binaries in a separate directory
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#PROJECT(MGpLib CXX)
#add_executable(${PROJECT_NAME} "main.cpp")






