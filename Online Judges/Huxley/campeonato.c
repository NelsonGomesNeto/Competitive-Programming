#include <stdio.h>

int main()
{
  int Cv, Ce, Cs, Cpontos;
  int Fv, Fe, Fs, Fpontos;
  scanf("%i %i %i %i %i %i", &Cv, &Ce, &Cs, &Fv, &Fe, &Fs);
  Cpontos = (Cv * 3) + Ce;
  Fpontos = (Fv * 3) + Fe;
  if (Cpontos > Fpontos)
  {
    printf("C\n");
  }
  else if (Fpontos > Cpontos)
  {
    printf("F\n");
  }
  else
  {
    if (Cs > Fs)
    {
      printf("C\n");
    }
    else if (Fs > Cs)
    {
      printf("F\n");
    }
    else
    {
      printf("=\n");
    }
  }
  return(0);
}
