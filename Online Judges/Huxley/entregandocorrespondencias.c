#include <stdio.h>

int main()
{
  int dias = 7, entrega, done = 0, media = 0;
  while (dias > 0)
  {
    scanf("%i", &entrega);
    if (entrega >= 100)
    {
      done ++;
    }
    media += entrega;
    dias --;
  }
  media /= 7;
  printf("%i\n%i\n", done, media);
  return(0);
}
