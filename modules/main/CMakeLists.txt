cmake_minimum_required(VERSION 3.15)

set(TBOX_MAIN_VERSION_MAJOR 1)
set(TBOX_MAIN_VERSION_MINOR 1)
set(TBOX_MAIN_VERSION_PATCH 2)
set(TBOX_MAIN_VERSION ${TBOX_MAIN_VERSION_MAJOR}.${TBOX_MAIN_VERSION_MINOR}.${TBOX_MAIN_VERSION_PATCH})

add_definitions(-DMODULE_ID="tbox.main")

set(TBOX_DEMO_NAME tbox_demo)

set(TBOX_MAIN_HEADERS
    context.h
    main.h
    module.h)

set(TBOX_MAIN_SOURCES
    main.cpp
)

set_target_properties(
    ${TBOX_LIBRARY_NAME} PROPERTIES
    VERSION ${TBOX_MAIN_VERSION}
    SOVERSION ${TBOX_MAIN_VERSION_MAJOR}
)

link_directories(${CMAKE_BINARY_DIR}/base)

add_executable(${TBOX_DEMO_NAME} ${TBOX_MAIN_SOURCES})
target_include_directories(${TBOX_DEMO_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/modules)
target_link_libraries(${TBOX_DEMO_NAME} PRIVATE tbox_base)
