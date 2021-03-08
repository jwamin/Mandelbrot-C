cmake_minimum_required(VERSION 3.17)
project(Brot C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#find_package(Cairo)

#link_directories(/usr/local/Cellar/cairo/1.16.0_3/lib)
#include_directories(${CAIRO_INCLUDE_DIRS})

add_executable(Brot main.c brot/brot.h brot/brot.c Rect/rect.c Rect/rect.h)

#include_directories(/usr/local/Cellar/jpeg/9d/include)

include(CheckSymbolExists)
check_symbol_exists(arc4random_uniform "stdlib.h" HASARC4RANDOM)
if(NOT (HASARC4RANDOM))
    target_link_libraries(Brot bsd)
    target_compile_definitions(Brot PRIVATE NOTHASARC4RANDOM)
endif ()

target_include_directories(Brot PRIVATE /usr/local/Cellar/jpeg/9d/include)
target_include_directories(Brot PRIVATE /usr/local/Cellar/jpeg/9d/lib)

target_link_libraries(Brot /usr/local/Cellar/jpeg/9d/lib/libjpeg.a)

#target_link_libraries(Brot cairo)