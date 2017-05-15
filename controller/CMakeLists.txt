cmake_minimum_required(VERSION 2.6)

project(controller)

set(AVR_MCU "atmega32u4")
set(AVR_FCPU "16000000")
set(ARDUINO_VARIANT "leonardo")

include(env.cmake)

add_definitions(-DARDUINO_ARCH_AVR)

include(${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arduino.cmake)

include_directories(${ARDUINO_PINS_DIR})
include_directories(${ARDUINO_CORE_DIR})

set(ARDUINO_SOURCE_FILES

        ${ARDUINO_CORE_DIR}/hooks.c
        ${ARDUINO_CORE_DIR}/wiring.c
        ${ARDUINO_CORE_DIR}/wiring_analog.c
        ${ARDUINO_CORE_DIR}/wiring_digital.c
        ${ARDUINO_CORE_DIR}/Print.cpp
        ${ARDUINO_CORE_DIR}/Stream.cpp
        ${ARDUINO_CORE_DIR}/WMath.cpp
        ${ARDUINO_CORE_DIR}/WString.cpp
        ${ARDUINO_CORE_DIR}/abi.cpp
        ${ARDUINO_CORE_DIR}/new.cpp
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
