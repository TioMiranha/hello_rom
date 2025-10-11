idf_component_register(SRCS "main.c" "src/Analog/pwm/pwmControl.c" "src/Analog/pwm/pwmConstructor.c" "src/utils/potencia.c"
    INCLUDE_DIRS "."
)

target_link_options(${COMPONENT_LIB} PRIVATE "-T${CMAKE_CURRENT_SOURCE_DIR}/hello_rom.ld")
