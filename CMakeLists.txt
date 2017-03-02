cmake_minimum_required(VERSION 2.6)

project(arduino-test)

include(cmake/build-env.cmake)

set(AVR_MCU "atmega328p")
set(AVR_FCPU "16000000")
set(ARDUINO_VARIANT "standard")

add_definitions(-DARDUINO_ARCH_AVR)

add_definitions(-DCMAKE_BUILD)


include(cmake/arduino.cmake)
include(cmake/avr-toolchain.cmake)

include_directories(${ARDUINO_PINS_DIR})
include_directories(${ARDUINO_CORE_DIR})

set(ARDUINO_SOURCE_FILES

        ${ARDUINO_CORE_DIR}/hooks.c
        ${ARDUINO_CORE_DIR}/wiring.c
        ${ARDUINO_CORE_DIR}/wiring_analog.c
        ${ARDUINO_CORE_DIR}/wiring_digital.c
        ${ARDUINO_CORE_DIR}/HardwareSerial.cpp
        ${ARDUINO_CORE_DIR}/HardwareSerial0.cpp
        ${ARDUINO_CORE_DIR}/Print.cpp
        ${ARDUINO_CORE_DIR}/Stream.cpp
        ${ARDUINO_CORE_DIR}/WMath.cpp
        ${ARDUINO_CORE_DIR}/WString.cpp
        ${ARDUINO_CORE_DIR}/abi.cpp
        ${ARDUINO_CORE_DIR}/new.cpp
        )

include_directories(src)

set(SOURCE_FILES
        ${ARDUINO_SOURCE_FILES}

        src/main.cpp
        )

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})