#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char padrao[20];
  int num[20];
  strcpy(padrao, "voupasrem1\0");
  int j;
  for (j = 0; padrao[j] != '\0'; j ++)
  {
    num[j] = 0;
  }
  char string;
  int i;
  while (scanf("%c", &string) != EOF)
  {
    for (j = 0; padrao[j] != '\0'; j ++)
    {
      if (tolower(string) == padrao[j])
      {
        num[j] += 1;
      }
    }
  }
  int soma = 0, still = 1;
  while (still == 1)
  {
    for (j = 0; j < 9; j ++)
    {
      if (j >= 3 && j <= 5)
      {
        if (num[j] - 2 < 0)
        {
          still = 0;
          break;
        }
        num[j] -= 2;
      }
      else
      {
        if (num[j] - 1 < 0)
        {
          still = 0;
          break;
        }
        num[j] -= 1;
      }
    }
    if (still == 1)
    {
      soma ++;
    }
  }
  printf("%d\n", soma);
  return(0);
}
