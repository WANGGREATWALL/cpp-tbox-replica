# CheckSymbolExists 是 CMake 自带的一个模块.
# 引入 CheckSymbolExists 模块就能够使用该模块提供的 check_symbol_exists 函数,
# 此函数可用于检查特定的符号 (如函数、变量等) 是否在系统的某个头文件中定义
include(CheckSymbolExists)

add_definitions(-DMODULE_ID="tbox.base")

set(TBOX_LIBRARY_NAME tbox_base)

# 查找当前文件夹下的所有头文件和源文件
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${TBOX_LIBRARY_NAME} ${SOURCE_FILES})
target_include_directories(${TBOX_LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})