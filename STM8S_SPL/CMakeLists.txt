cmake_minimum_required (VERSION 3.0)
set(PROJECT STM8S_SPL)
project(${PROJECT} C)

add_definitions(-D STM8S103)

include_directories( ${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/inc)

set(SOURCES blinky.c
    ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_adc1.c)

add_executable(${PROJECT} ${SOURCES})
