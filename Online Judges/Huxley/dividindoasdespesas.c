#include <stdio.h>

int main()
{
  char nome[5]; int convert, repeat;
  float dinC = 0, dinD = 0, din, deve;
  for (repeat = 0; repeat < 6; repeat ++)
  {
    scanf("%f", &din);
    scanf("%s", &*nome);
    for (convert = 0; convert < 5; convert ++)
    {
      nome[convert] = tolower(nome[convert]);
    }
    if (strcmp(nome,"clara") == 0)
    {
      dinC += din / 2;
    }
    else { dinD += din / 2; }
  }
  if (dinD > dinC)
  {
    deve = dinD - dinC;
    printf("CLARA\n%.2f\n", deve);
  }
  else if (dinC > dinD)
  {
    deve = dinC - dinD;
    printf("DIANA\n%.2f\n", deve);
  }
  else { printf("MORADORAS QUITES\n"); }
  return(0);
}
