#include <stdio.h>

int main()
{
  int notas[3], i;
  for (i = 0; i < 3; i ++)
    scanf("%d", &notas[i]);

  int o, b, aux;
  for (o = 0; o < 3; o ++)
    for (b = o + 1; b < 3; b ++)
      if (notas[o] > notas[b])
      {
        aux = notas[o];
        notas[o] = notas[b];
        notas[b] = aux;
      }

  for (i = 0; i < 3; i ++)
    printf("%d\n", notas[i]);

  return(0);
}
