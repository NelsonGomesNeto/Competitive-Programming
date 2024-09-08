#include <stdio.h>

int main()
{
  int num[500], tam = 0; float media = 0;
  while (scanf("%d", &num[tam]) != EOF)
  {
    media += num[tam];
    tam ++;
  }
  media /= tam;
  printf("Media = %.1f\n", media);
  return(0);
}
