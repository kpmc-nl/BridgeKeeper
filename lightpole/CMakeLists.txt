cmake_minimum_required(VERSION 2.6)

# let cmake know we are cross-compiling
set(CMAKE_SYSTEM_NAME Generic)

project(lightpole)

include(env.cmake)

set(AVR_MCU "attiny45")
set(AVR_FCPU "1000000")

add_definitions(-DARDUINO_ARCH_AVR)

#set(AVRDUDE_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/avrdude.conf")

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

include_directories(../manchester)
include_directories(../protocol)

set(SOURCE_FILES
        ${ARDUINO_SOURCE_FILES}

        ../manchester/Manchester.h
        ../manchester/Manchester.cpp

        main.cpp
        )

# A phony executable for this module, to keep cmake happy
add_executable(${PROJECT_NAME} ${SOURCE_FILES})