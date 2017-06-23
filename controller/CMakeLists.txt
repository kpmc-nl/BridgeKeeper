cmake_minimum_required(VERSION 2.6)

project(controller)

set(AVR_MCU "atmega32u4")
set(AVR_FCPU "16000000")
set(ARDUINO_VARIANT "leonardo")

include(env.cmake)

add_definitions(-DARDUINO_ARCH_AVR)
add_definitions(-DARDUINO=182)

include(${CMAKE_SOURCE_DIR}/cmake/arduino.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake)

include_directories(${ARDUINO_LIB_DIR}/Wire/src)

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

        ${ARDUINO_LIB_DIR}/Wire/src/Wire.cpp
        ${ARDUINO_LIB_DIR}/Wire/src/utility/twi.c

        )

include_directories(../manchester)
include_directories(../protocol)
include_directories(../MPU6050)
include_directories(../I2Cdev)
#
set(SOURCE_FILES
        ${ARDUINO_SOURCE_FILES}

        ../manchester/Manchester.h
        ../manchester/Manchester.cpp

        ../I2Cdev/I2Cdev.cpp
        ../MPU6050/MPU6050.cpp

        main.cpp

        )

add_avr_firmware(${PROJECT_NAME} ${SOURCE_FILES})
