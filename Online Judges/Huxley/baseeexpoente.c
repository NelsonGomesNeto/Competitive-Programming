#include <stdio.h>

int main()
{
  int base, expoente;
  printf("Informe a base:\n");
  scanf("%d", &base);
  printf("Informe o expoente:\n");
  scanf("%d", &expoente);
  int i, pot = 1;
  for (i = 0; i < expoente; i ++)
  {
    pot *= base;
  }
  printf("Resultado: %d\n", pot);
  return(0);
}
