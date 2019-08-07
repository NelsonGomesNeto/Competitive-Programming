#include <stdio.h>
#include <string.h>

int check(char p[], int i, int tam)
{
  if (i == tam / 2)
  {
    return(1);
  }
  if (p[i] != p[tam - 1 - i])
  {
    return(0);
  }
  check(p, i + 1, tam);
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    char num[99], aux[99]; int i;
    for (i = 0; i < 99; i ++)
    {
      aux[i] = '\0';
      num[i] = '\0';
    }
    getchar();
    scanf("%s", num);
    i = 0;
    while (num[i] == '0')
    {
      i ++;
    }
    if (i > 0 && i != strlen(num))
    {
      int j;
      for (j = 0; i < strlen(num); i ++, j++)
      {
        num[j] = num[i];
      }
      num[j] = '\0';
    }
    int steps = 0;
    while (check(num, 0, strlen(num)) == 0)
    {
      int soma;
      for (i = 0; i < strlen(num); i ++)
      {
        aux[i] = num[strlen(num) - 1 - i];
      }
      soma = atoi(num) + atoi(aux);
      sprintf(num, "%d", soma);
      //printf("%s\n", num);
      steps ++;
    }
    printf("%d %s\n", steps, num);
    tests --;
  }
  return(0);
}
