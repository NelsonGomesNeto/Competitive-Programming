#include <stdio.h>
#include <string.h>

char stringA[99999], stringB[99999], permu[99999], aux;

int ler()
{
  scanf("%[^\n]", stringA);
  getchar();
  scanf("%[^\n]", stringB);
  if (strcmp(stringA,stringB) == 0)
  {
    return(1);
  }
  return(0);
}

int main()
{
  while (ler() == 0)
  {
    int chA, chB, posi = 0, zerar, tamA = strlen(stringA), tamB = strlen(stringB);
    for (chA = 0; chA < tamA; chA ++)
    {
      for (chB = 0; chB < tamB; chB ++)
      {
        if (stringA[chA] == stringB[chB])
        {
          permu[posi] = stringA[chA];
          stringA[chA] = 'A';
          stringB[chB] = 'B';
          posi ++;
        }
      }
    }
    for (chA = 0; chA < strlen(permu); chA ++)
    {
      for (chB = chA; chB < strlen(permu); chB ++)
      {
        if (permu[chA] > permu[chB])
        {
          aux = permu[chA];
          permu[chA] = permu[chB];
          permu[chB] = aux;
        }
      }
    }
    printf("%s\n", permu);
    for (zerar = 0; zerar < 99999; zerar ++)
    {
      stringA[zerar] = '\0';
      stringB[zerar] = '\0';
      permu[zerar] = '\0';
    }
    getchar();
  }
  printf("\n\n\n");
  return(0);
}
