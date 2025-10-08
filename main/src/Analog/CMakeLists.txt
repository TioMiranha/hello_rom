idf_component_register(
  SRCS "Analog/pwm/pwmControl.c" "Analog/pwm/pwmConstructor.c" "src/utils/potencia.c"
  INCLUDE_DIRS "." "includes" "src/utils/includes"
  REQUIRES esp_driver_dac

)
