#include <stdio.h>

int main()
{
  int PC, cabos, copia = 1, horas = 0, insta = 0; scanf("%d %d", &PC, &cabos); PC --;
  while (PC > 0)
  {
    insta += copia;
    PC -= copia;
    //printf("cable %d PC %d\n", copia, PC);
    if (copia < cabos)
    {
      copia += insta;
    }
    if (copia > cabos)
    {
      copia = cabos;
    }
    horas ++;
  }
  printf("%d\n", horas);
  return(0);
}
