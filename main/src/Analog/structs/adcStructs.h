#ifndef ADCSTRUCT_H
#define ADCSTRUCT_H

typedef struct
{
  float setpoint;
  float kp, ki, kd;
  float integral;
  float previous_error;
} pid_controller_t;

#endif