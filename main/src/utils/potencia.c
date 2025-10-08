#include ".././Analog/includes/pwmInclude.h"

double potencia(double x, int y)
{
  int i;
  double resultado = 1.0;

  if (y == 0)
    return 1.0;

  int positivo = y > 0 ? 1 : 0;

  if (!positivo)
    return y = -y;

  for (i = 0; i < y; i++)
  {
    resultado *= x;
  }

  if (!positivo)
    return resultado = 1.0 / resultado;

  return resultado;
}