cmake_minimum_required (VERSION 3.0)
set(PROJECT STM8S_SPL_RX)
project(${PROJECT} C)

add_definitions(-D STM8S103)
add_definitions(-D RECEIVER)

include_directories( ${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/inc)

set(SOURCES
    rx.c
#    adc.c
    serial.c
    print.c
    timer4.c
    spi.c
    nrf24.c
#    pwm.c
#    ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_tim2.c
    )

add_executable(${PROJECT} ${SOURCES})

#set(PROJECT STM8S_SPL_TX)
#project(${PROJECT} C)

#add_definitions(-D STM8S103)

#include_directories( ${CMAKE_SOURCE_DIR}
#                     ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/inc)

#set(SOURCES
#    tx.c
##    adc.c
#    serial.c
#    print.c
#    timer4.c
#    spi.c
#    nrf24.c
##    pwm.c
##    ${CMAKE_SOURCE_DIR}/../STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_tim2.c
#    )

#add_executable(${PROJECT} ${SOURCES})
