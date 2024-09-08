#include <stdio.h>

int main()
{
  int dia, mes, ano, countdown = 30;
  scanf("%d/%d/%d", &dia, &mes, &ano);
  int months[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (( (ano % 4 == 0) && (ano % 100 != 0) ) || (ano % 400 == 0))
  {
    months[2] = 29;
  }
  while (countdown > 0)
  {
    dia ++;
    if (dia > months[mes])
    {
      mes ++;
      dia = 1;
    }
    if (mes > 12)
    {
      mes = 1; ano ++;
    }
    countdown --;
  }
  printf("%02d/%02d/%d\n", dia, mes, ano);
  return(0);
}
