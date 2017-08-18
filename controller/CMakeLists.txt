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

include_directories(../lib/manchester)
include_directories(../protocol)
include_directories(../lib/MPU6050)
include_directories(../lib/I2Cdev)
include_directories(../lib/LiquidCrystal)
#
set(SOURCE_FILES
        ${ARDUINO_SOURCE_FILES}

        ../lib/manchester/Manchester.h
        ../lib/manchester/Manchester.cpp

        ../lib/I2Cdev/I2Cdev.cpp
        ../lib/MPU6050/MPU6050.cpp

        ../lib/LiquidCrystal/LiquidCrystal_I2C.h
        ../lib/LiquidCrystal/LiquidCrystal_I2C.cpp

        ../lib/LiquidCrystal/LCD.h
        ../lib/LiquidCrystal/LCD.cpp

        ../lib/LiquidCrystal/I2CIO.h
        ../lib/LiquidCrystal/I2CIO.cpp

        Controller.h Controller.cpp
        State.h Pinout.h
        AngleSensor.h AngleSensor.cpp
        BridgeActuator.h BridgeActuator.cpp
        Receiver.h Receiver.cpp
        UI.h UI.cpp
        Button.h Button.cpp

        main.cpp

        )

add_avr_firmware(${PROJECT_NAME} ${SOURCE_FILES})
