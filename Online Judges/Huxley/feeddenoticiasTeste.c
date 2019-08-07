#include <stdio.h>
#include <string.h>

int procura(int lugar, int tudo[], int tam)
{
  int look;
  for (look = 0; look < tam; look ++)
  {
    if (tudo[look] == lugar)
    {
      //printf("#%d#\n", look);
      return (look);
    }
  }
}

int main()
{
  int feed; scanf("%d", &feed);
  int friends; scanf("%d", &friends);
  float proxim[friends]; int posi, amigo[friends], ler, clean;
  for (ler = 0; ler < friends; ler ++)
  {
    scanf("%d", &amigo[ler]);
    posi = amigo[ler];
    scanf("%f", &proxim[procura(posi, amigo, friends)]);
  }
  int updates; scanf("%d", &updates);
  float tempo[updates], auxFloat; char frase[updates][99999], auxWord[99999];
  for (ler = 0; ler < updates; ler ++)
  {
    scanf("%d", &posi); scanf("%f", &tempo[procura(posi, amigo, friends)]);
    if (strlen(frase[procura(posi, amigo, friends)]) > 0)
    {
      for (clean = 0; clean < 100000; clean ++)
      {
        frase[procura(posi, amigo, friends)][clean] = '\0';
      }
    }
    getchar(); scanf("%[^\n]", frase[procura(posi, amigo, friends)]);
  }
  for (ler = 0; ler < friends; ler ++)
  {
    for (posi = ler; posi < friends; posi ++)
    {
      if ((proxim[ler] * 0.8) + (tempo[ler] * 0.2) <= (proxim[posi] * 0.8) + (tempo[posi] * 0.2))
      {
        auxFloat = proxim[ler];
        proxim[ler] = proxim[posi];
        proxim[posi] = auxFloat;

        auxFloat = amigo[ler];
        amigo[ler] = amigo[posi];
        amigo[posi] = auxFloat;

        auxFloat = tempo[ler];
        tempo[ler] = tempo[posi];
        tempo[posi] = auxFloat;

        strcpy(auxWord, frase[ler]);
        strcpy(frase[ler], frase[posi]);
        strcpy(frase[posi], auxWord);
      }
    }
  }
  for (ler = 0; ler < feed; ler ++)
  {
    printf("%d %s\n", amigo[ler], frase[amigo[ler]]);
  }
  return(0);
}
