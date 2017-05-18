
if (NOT ARDUINO_PATH)
    message(FATAL_ERROR "Specify the Arduino SDK path in the textfile build-env.cmake")
endif ()

enable_language(ASM)

set(ARDUINO_CORE_DIR "${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino/")
set(ARDUINO_PINS_DIR "${ARDUINO_PATH}/hardware/arduino/avr/variants/${ARDUINO_VARIANT}")
set(ARDUINO_LIB_DIR "${ARDUINO_PATH}/hardware/arduino/avr/libraries")

if (NOT AVRDUDE_CONFIG)
    set(AVRDUDE_CONFIG "${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf")
endif ()

set(AVR_GCC ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-gcc)
set(AVR_G++ ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-g++)
set(AVR_OBJCOPY ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy)
set(AVRDUDE ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${AVRDUDE_CONFIG})

include_directories(${ARDUINO_PINS_DIR})
include_directories(${ARDUINO_CORE_DIR})