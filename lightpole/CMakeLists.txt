cmake_minimum_required(VERSION 2.6)

project(lightpole)

include(env.cmake)

set(AVR_MCU "attiny45")
set(AVR_FCPU "8000000")

include(${CMAKE_SOURCE_DIR}/cmake/avr-toolchain.cmake)

include_directories(src)

set(SOURCE_FILES

        src/Manchester.h src/Manchester.cpp
        src/main.cpp
        )

# A phony executable for this module, to keep cmake happy
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
