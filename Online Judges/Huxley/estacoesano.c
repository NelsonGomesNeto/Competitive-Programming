#include <stdio.h>

int main()
{
  int dia, mes;
  scanf("%i\n%i", &dia, &mes);
  if (mes >= 9 && mes <= 12)
  {
    if (mes == 9 || mes == 12)
    {
      if (mes == 9 && dia >= 21)
      {
        printf("PRIMAVERA\n");
      }
      else if (mes == 12 && dia <= 20)
      {
        printf("PRIMAVERA\n");
      }
    }
    else
    {
      printf("PRIMAVERA\n");
    }
  }
  if (mes >= 12 || mes <= 3)
  {
    if (mes == 12 || mes == 3)
    {
      if (mes == 12 && dia >= 21)
      {
        printf("VERAO\n");
      }
      else if (mes == 3 && dia <= 20)
      {
        printf("VERAO\n");
      }
    }
    else
    {
      printf("VERAO\n");
    }
  }
  if (mes >= 3 && mes <= 6)
  {
    if (mes == 3 || mes == 6)
    {
      if (mes == 3 && dia >= 21)
      {
        printf("OUTONO\n");
      }
      else if (mes == 6 && dia <= 20)
      {
        printf("OUTONO\n");
      }
    }
    else
    {
      printf("OUTONO\n");
    }
  }
  if (mes >= 6 && mes <= 9)
  {
    if (mes == 6 || mes == 9)
    {
      if (mes == 6 && dia >= 21)
      {
        printf("INVERNO\n");
      }
      else if (mes == 9 && dia <= 20)
      {
        printf("INVERNO\n");
      }
    }
    else
    {
      printf("INVERNO\n");
    }
  }
  return(0);
}
