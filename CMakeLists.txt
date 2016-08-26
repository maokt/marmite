cmake_minimum_required(VERSION 2.8)
project(marmite C)

set_property(GLOBAL PROPERTY CMAKE_C_STANDARD 99)
set_property(GLOBAL PROPERTY CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_search_module(VTE REQUIRED vte-2.91 vte-2.90)

link_libraries(
    ${GLIB2_LIBRARIES}
    ${GTK3_LIBRARIES}
    ${VTE_LIBRARIES}
    )
include_directories(
    ${GLIB2_INCLUDE_DIRS}
    ${GTK3_INCLUDE_DIRS}
    ${VTE_INCLUDE_DIRS}
    )
add_compile_options(
    ${GLIB2_CFLAGS_OTHER}
    ${GTK3_CFLAGS_OTHER}
    ${VTE_CFLAGS_OTHER}
    )

add_library(objects OBJECT config.c term.c)

add_executable(marmite marmite.c $<TARGET_OBJECTS:objects>)
add_executable(unittests unittests.c $<TARGET_OBJECTS:objects>)

enable_testing()
add_test(NAME simple COMMAND unittests)
