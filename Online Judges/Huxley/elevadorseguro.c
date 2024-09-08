#include <stdio.h>

int main()
{
  int pessoas = 0;
  float peso = 0, total = 0;
  while (pessoas <= 7 && total <= 560 && (peso != 0 || pessoas == 0))
  {
    scanf("%f", &peso);
    total += peso;
    pessoas ++;
  }
  pessoas --;
  total -= peso;
  printf("%i\n%.1f\n", pessoas, total);
  return(0);
}
