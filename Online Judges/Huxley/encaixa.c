#include <stdio.h>

int encaixa(int a, int b)
{
  if (a < b) return(0);

  int pot = 1;
  while (b >= pot)
    pot *= 10;

  if (a % pot == b) return(1);
  else                     return(0);
}

int main(void)
{
    int x, y;

    scanf("%d%d", &x, &y);

    while (x != -1) // lê enquanto x for diferente de -1
    {
        printf("%d\n", encaixa(x, y) );
        scanf("%d%d", &x, &y);
    }
	return 0;
}
