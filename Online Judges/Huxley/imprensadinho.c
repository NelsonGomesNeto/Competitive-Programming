#include <stdio.h>

int main()
{
  int numeroDoAmbrosio, num; scanf("%d", &numeroDoAmbrosio);
  int start = 0, end = 100;
  while (scanf("%d", &num))
  {
    if (num == numeroDoAmbrosio)
    {
      printf("Voce bebe!\n"); break;
    }
    if (num < numeroDoAmbrosio) { start = num; }
    if (num > numeroDoAmbrosio) { end = num; }
    if (start + 1 == numeroDoAmbrosio && end - 1 == numeroDoAmbrosio)
    {
      printf("Ambrosio bebe!\n"); break;
    }
    else
    {
      printf("Escolha um numero entre %d e %d!\n", start, end);
    }
  }
  return(0);
}
