#ifndef MODBUS_H
#define MODBUS_H

#include "generalIncludes.h"
#include "pwmConstructor.h"
#include "mbc_tcp_slave.h"

void initilizeRegisterModbus(int index, output_channel_t out_initialze_register);
void initializeModbus(void);

extern mb_register_area_descriptor_t reg_area;
#endif
