cmake_minimum_required(VERSION 2.8)

aux_source_directory(. srcs)

include_directories(${PROJECT_SOURCE_DIR} )

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 生成动态库目标
add_library(antlr SHARED ${srcs})
# 生成静态库目标
add_library(antlr_static STATIC ${srcs})

# 指定静态库的输出名称
set_target_properties(antlr_static PROPERTIES OUTPUT_NAME "antlr")
# 使动态库和静态库同时存在
set_target_properties(antlr PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(antlr_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
