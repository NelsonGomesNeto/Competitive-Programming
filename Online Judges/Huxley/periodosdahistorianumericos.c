#include <stdio.h>
#include <string.h>

int ordem(int num[3], int num2[3])
{
  int ordem, bubble, aux;
  for (ordem = 0; ordem < 3; ordem ++)
  {
    for (bubble = ordem; bubble < 3; bubble ++)
    {
      if (num[ordem] > num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
        aux = num2[ordem];
        num2[ordem] = num2[bubble];
        num2[bubble] = aux;
      }
    }
  }
}

int main()
{
  int ano[3], abso[3], ler, convert, aux; char era[3][2];

  for (ler = 0; ler < 3; ler ++)
  {
    scanf("%i\n%s", &ano[ler], era[ler]);
    for (convert = 0; convert < 2; convert ++)
    {
      era[ler][convert] = tolower(era[ler][convert]);
    }
    if (strcmp(era[ler],"ac") == 0)
    {
      abso[ler] = ano[ler] * (-1);
    }
    else
    {
      abso[ler] = ano[ler];
    }
  }

  ordem(&*abso, &*ano);

  if (strcmp(era[2],"ac") == 0)
  {
    if (ano[2] >= 4000)
    {
      printf("1\n");
    }
    else
    {
      printf("2\n");
    }
  }
  else
  {
    if (ano[2] <= 476)
    {
      printf("2\n");
    }
    else if (ano[2] <= 1789)
    {
      printf("3\n");
    }
    else if (ano[2] > 1789)
    {
      printf("4\n");
    }
  }
  return(0);
}
