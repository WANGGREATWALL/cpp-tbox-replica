cmake_minimum_required(VERSION 3.15)

#
# build 目录不能被指定为和源文件目录相同, 否则会污染工作目录
#
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

#
# 解析 version.mk 中的版本号
#
file(STRINGS "version.mk" VERSION_CONTENTS)
set(REGEX_MAJOR "TBOX_VERSION_MAJOR *:= *([0-9]+)")
set(REGEX_MINOR "TBOX_VERSION_MINOR *:= *([0-9]+)")
set(REGEX_REVISION "TBOX_VERSION_REVISION *:= *([0-9]+)")
string(REGEX MATCH "${REGEX_MAJOR}" _ ${VERSION_CONTENTS})
set(TBOX_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "${REGEX_MINOR}" _ ${VERSION_CONTENTS})
set(TBOX_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "${REGEX_REVISION}" _ ${VERSION_CONTENTS})
set(TBOX_VERSION_REVISION ${CMAKE_MATCH_1})

set(TBOX_VERSION ${TBOX_VERSION_MAJOR}.${TBOX_VERSION_MINOR}.${TBOX_VERSION_REVISION})

#
# 设置 project 属性
#
project(
    cpp-tbox-replica
    VERSION ${TBOX_VERSION}
    DESCRIPTION "Easy to use, convenient and modern C++ treasure box!"
    HOMEPAGE_URL "https://gitee.com/cpp-master/cpp-tbox"
    LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(TBOX_BUILD_LIB_TYPE STATIC)

message("*")
message("* ${PROJECT_NAME} v${PROJECT_VERSION} (${CMAKE_BUILD_TYPE})")
message("* Copyright (c) 2020-2025 Hevake,Lucas")
message("*")

#
# 模块开关
#
option(TBOX_ENABLE_BASE "build base" ON)
option(TBOX_ENABLE_UTIL "build util" OFF)
option(TBOX_ENABLE_EVENT "build event" OFF)
option(TBOX_ENABLE_EVENTX "build eventx" OFF)
option(TBOX_ENABLE_LOG "build log" OFF)
option(TBOX_ENABLE_NETWORK "build network" OFF)
option(TBOX_ENABLE_TERMINAL "build terminal" OFF)
option(TBOX_ENABLE_TRACE "build trace" OFF)
option(TBOX_ENABLE_MAIN "build main" ON)

option(TBOX_ENABLE_COROUTINE "build coroutine" OFF)
option(TBOX_ENABLE_HTTP "build http" OFF)
option(TBOX_ENABLE_MQTT "build mqtt" OFF)
option(TBOX_ENABLE_FLOW "build flow" OFF)
option(TBOX_ENABLE_ALARM "build alarm" OFF)
option(TBOX_ENABLE_CRYPTO "build crypto" OFF)
option(TBOX_ENABLE_JSONRPC "build jsonrpc" OFF)
option(TBOX_ENABLE_DBUS "build dbus" OFF)

#
# 3rd-party libraries
#
option(TBOX_ENABLE_NLOHMANN_JSON "install nlohmann/json" ON)

include(GNUInstallDirs)

#
# 编译参数
#
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Werror -Wno-missing-field-initializers)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_definitions(-DTBOX_VERSION_MAJOR=${TBOX_VERSION_MAJOR}
                -DTBOX_VERSION_MINOR=${TBOX_VERSION_MINOR}
                -DTBOX_VERSION_REVISION=${TBOX_VERSION_REVISION})

set(TBOX_COMPONENTS)

if(TBOX_ENABLE_BASE)
    message(STATUS "base module enabled")
    list(APPEND TBOX_COMPONENTS base)
endif()

if(TBOX_ENABLE_UTIL)
    message(STATUS "util module enabled")
    list(APPEND TBOX_COMPONENTS util)
endif()

if(TBOX_ENABLE_EVENT)
    message(STATUS "event module enabled")
    list(APPEND TBOX_COMPONENTS event)
endif()

if(TBOX_ENABLE_EVENTX)
    message(STATUS "eventx module enabled")
    list(APPEND TBOX_COMPONENTS eventx)
endif()

if(TBOX_ENABLE_LOG)
    message(STATUS "log module enabled")
    list(APPEND TBOX_COMPONENTS log)
endif()

if(TBOX_ENABLE_NETWORK)
    message(STATUS "network module enabled")
    list(APPEND TBOX_COMPONENTS network)
endif()

if(TBOX_ENABLE_TERMINAL)
    message(STATUS "terminal module enabled")
    list(APPEND TBOX_COMPONENTS terminal)
endif()

if(TBOX_ENABLE_TRACE)
    message(STATUS "trace module enabled")
    list(APPEND TBOX_COMPONENTS trace)
endif()

if(TBOX_ENABLE_MAIN)
    message(STATUS "main module enabled")
    list(APPEND TBOX_COMPONENTS main)
endif()

if(TBOX_ENABLE_COROUTINE)
    message(STATUS "coroutine module enabled")
    list(APPEND TBOX_COMPONENTS coroutine)
endif()

if(TBOX_ENABLE_HTTP)
    message(STATUS "http module enabled")
    list(APPEND TBOX_COMPONENTS http)
endif()

if(TBOX_ENABLE_MQTT)
    message(STATUS "mqtt module enabled")
    list(APPEND TBOX_COMPONENTS mqtt)
endif()

if(TBOX_ENABLE_FLOW)
    message(STATUS "flow module enabled")
    list(APPEND TBOX_COMPONENTS flow)
endif()

if(TBOX_ENABLE_ALARM)
    message(STATUS "alarm module enabled")
    list(APPEND TBOX_COMPONENTS alarm)
endif()

if(TBOX_ENABLE_CRYPTO)
    message(STATUS "crypto module enabled")
    list(APPEND TBOX_COMPONENTS crypto)
endif()

if(TBOX_ENABLE_JSONRPC)
    message(STATUS "jsonrpc module enabled")
    list(APPEND TBOX_COMPONENTS jsonrpc)
endif()

if(TBOX_ENABLE_DBUS)
    message(STATUS "dbus module enabled")
    list(APPEND TBOX_COMPONENTS dbus)
endif()

foreach(item IN LISTS TBOX_COMPONENTS)
    add_subdirectory(modules/${item})
endforeach()

if(TBOX_ENABLE_NLOHMANN_JSON)
    message(STATUS "nlohmann/json installation enabled")
    list(APPEND TBOX_COMPONENTS nlohmann)
    add_subdirectory(3rd-party/nlohmann)
endif()