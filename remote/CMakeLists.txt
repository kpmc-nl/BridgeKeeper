cmake_minimum_required(VERSION 2.6)

project(remote)

set(AVR_MCU "attiny841")
set(AVR_FCPU "8000000")
set(AVRDUDE_OPTIONS -C${CMAKE_CURRENT_SOURCE_DIR}/avrdude.conf)

include(env.cmake)

add_definitions(-DARDUINO_ARCH_AVR)

include(${CMAKE_SOURCE_DIR}/cmake/arduino.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake)

include_directories(${ATTINY_CORE_PATH}/avr/cores/tinymodern)
include_directories(src)

set(ARDUINO_SOURCE_FILES
        ${ATTINY_CORE_PATH}/avr/cores/tinymodern/pins_arduino.c
        ${ATTINY_CORE_PATH}/avr/cores/tinymodern/WInterrupts.c
        ${ATTINY_CORE_PATH}/avr/cores/tinymodern/wiring.c
        ${ATTINY_CORE_PATH}/avr/cores/tinymodern/wiring_analog.c
        ${ATTINY_CORE_PATH}/avr/cores/tinymodern/wiring_digital.c
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
