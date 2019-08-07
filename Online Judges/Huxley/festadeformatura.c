#include <stdio.h>

int main()
{
  int convidados, total = 0;
  float multa = 0;
  while (scanf("%i", &convidados) && convidados >= 0)
  {
    if (convidados > 25)
    {
      convidados = 25;
    }
    if (convidados > 15)
    {
      multa += (convidados - 15) * 42;
    }
    total += convidados + 1;
  }
  printf("%.2f\n%i\n", multa, total);
  return(0);
}
