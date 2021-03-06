cmake_minimum_required(VERSION 2.6)

project(lightpole)

set(AVR_MCU "attiny45")
set(AVR_FCPU "1000000")
set(ATTINY_CORE_PATH ../lib/ATTinyCore)

include(env.cmake)

add_definitions(-DARDUINO_ARCH_AVR)

include(${CMAKE_SOURCE_DIR}/cmake/arduino.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake)

include_directories(${ATTINY_CORE_PATH}/avr/cores/tiny)
include_directories(${ATTINY_CORE_PATH}/avr/variants/tinyX5)

include_directories(src)

set(ARDUINO_SOURCE_FILES

        ${ATTINY_CORE_PATH}/avr/cores/tiny/WInterrupts.c
        ${ATTINY_CORE_PATH}/avr/cores/tiny/wiring.c
        ${ATTINY_CORE_PATH}/avr/cores/tiny/wiring_analog.c
        ${ATTINY_CORE_PATH}/avr/cores/tiny/wiring_digital.c
        )

include_directories(../lib/manchester)
include_directories(../protocol)

set(SOURCE_FILES
        ${ARDUINO_SOURCE_FILES}

        ../lib/manchester/Manchester.h
        ../lib/manchester/Manchester.cpp

        main.cpp
        )

add_avr_firmware(${PROJECT_NAME} ${SOURCE_FILES})