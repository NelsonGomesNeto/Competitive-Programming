#include <stdio.h>

int main()
{
  int pag, ultima = 0, dif = 0, repeat;
  scanf("%i", &pag);
  for (repeat = 0; repeat < 7; repeat ++)
  {
    scanf("%i", &pag);
    if (pag - ultima > dif)
    {
      dif = pag - ultima;
    }
    ultima = pag;
  }
  printf("%i\n%i\n", ultima, dif);
  return(0);
}
