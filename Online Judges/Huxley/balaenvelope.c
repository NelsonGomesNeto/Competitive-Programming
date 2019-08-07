#include <stdio.h>

int main()
{
  int numeroenvolopes, menorenvelope, menorbala;
  scanf("%i", &numeroenvolopes);
  scanf("%i", &menorbala);
  numeroenvolopes --;
  menorenvelope = menorbala;
  while (numeroenvolopes > 0)
  {
    scanf("%i", &menorbala);
    if (menorbala < menorenvelope)
    {
      menorenvelope = menorbala;
    }
    numeroenvolopes --;
  }
  printf("%i\n", menorenvelope);
  return(0);
}
