cmake_minimum_required(VERSION 2.8)
project(marmite C)
add_executable(marmite marmite.c args.c look.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_search_module(VTE REQUIRED vte-2.91 vte-2.90)

target_link_libraries(marmite
    PUBLIC ${GLIB2_LIBRARIES}
    PUBLIC ${GTK3_LIBRARIES}
    PUBLIC ${VTE_LIBRARIES}
    )
target_include_directories(marmite
    PUBLIC ${GLIB2_INCLUDE_DIRS}
    PUBLIC ${GTK3_INCLUDE_DIRS}
    PUBLIC ${VTE_INCLUDE_DIRS}
    )
target_compile_options(marmite
    PUBLIC ${GLIB2_CFLAGS_OTHER}
    PUBLIC ${GTK3_CFLAGS_OTHER}
    PUBLIC ${VTE_CFLAGS_OTHER}
    )

