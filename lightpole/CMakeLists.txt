project(lightpole)

cmake_minimum_required(VERSION 2.6)

set(AVRDUDE_PROGRAMMER_FLAGS -cstk500 -P/dev/ttyUSB0)
set(AVR_MCU "attiny45")
set(AVR_FCPU "8000000")

include(cmake/avr-toolchain.cmake)

include_directories(src)

set(SOURCE_FILES

        src/Manchester.h src/Manchester.cpp
        src/main.cpp
        )

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
