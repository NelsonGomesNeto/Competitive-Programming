#include <stdio.h>

int main()
{
  int jogos; float total, bonus, salario;
  scanf("%i", &jogos);
  total = 19.9 * jogos;
  if (jogos >= 15)
  {
    bonus = total * 0.08 * (jogos / 15);
  }
  salario = (total * 0.5) + bonus;
  printf("%.2f\n%.2f\n%.2f\n", total, bonus, salario);
  return(0);
}
