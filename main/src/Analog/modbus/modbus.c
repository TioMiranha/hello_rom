#include "../includes/modbus.h"

// Este é o registrador Holding que será acessível via Modbus
#define MB_REG_DUTY_CYCLE_0 0
#define MB_REG_DUTY_CYCLE_1 1
#define MB_REG_DUTY_CYCLE_2 2
#define MB_REG_DUTY_CYCLE_3 3

typedef struct
{
  int reg_id;
} modbus_registers;

modbus_registers addr_regs[4] = {
    {MB_REG_DUTY_CYCLE_0},
    {MB_REG_DUTY_CYCLE_1},
    {MB_REG_DUTY_CYCLE_2},
    {MB_REG_DUTY_CYCLE_3},
};

// Variável que armazena o valor do duty cycle (0-8191 para 13 bits)

void initializeModbus(void)
{
  ESP_ERROR_CHECK(mbc_slave_init_tcp(&slave_handler));

  // Inicia o controlador Modbus
  ESP_ERROR_CHECK(mbc_slave_start());
}

void initilizeRegisterModbus(int index, output_channel_t out_initialzer_register)
{
  mb_register_area_descriptor_t reg_area;
  reg_area.type = MB_PARAM_HOLDING;
  reg_area.start_offset = addr_regs[i];
  reg_area.address = (void *)&outputs[index].voltage_duty;
  reg_area.size = sizeof(outputs[index].voltage_duty);
  ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
}

void updadePwmWithModbusData(int index, output_channel_t *outputs_default_duty)
{
  if (defineModeAnalog(index, *outputs_default_duty) == 1)
  {
    outputs_default_duty[index].voltage_duty = (outputs_default_duty[index].voltage_duty * 8191) / 10000;

    if (outputs[i].current_duty >= 7145)
      outputs[i].current_duty = 1112;
  }
  else
  {
    outputs_default_duty[index].voltage_duty = (outputs_default_duty[index].current_duty * 8191) / 10000;

    if (outputs[i].current_duty >= 7145)
      outputs[i].current_duty = 1112;
  }
}