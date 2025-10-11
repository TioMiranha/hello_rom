#include "./includes/allUtilsIncludes.h"

int defineModeAnalog(int index, output_channel_t out_mode)
{
  if (out_mode[index].mode == 1)
    return 1;
  else
    return 0;
}

int isAnalogEnabled(int index, output_channel_t is_enabled)
{
  if (is_enabled[index].enabled == 1)
    return 1;
  else
    return 0;
}
