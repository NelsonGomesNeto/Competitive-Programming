#include <stdio.h>
#include <string.h>

int procura(int lugar, int tudo[], int tam)
{
  int look;
  for (look = 0; look < tam; look ++)
  {
    if (tudo[look] == lugar)
    {
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
    scanf("%d", &posi); scanf("%f", &proxim[ler]);
    amigo[ler] = posi;
  }
  int updates, post[updates]; scanf("%d", &updates);
  float tempo[updates], auxFloat; char frase[updates][100000], auxWord[100000];
  for (ler = 0; ler < friends; ler ++)
  {
    for (posi = ler; posi < friends; posi ++)
    {
      if (amigo[ler] > amigo[posi])
      {
        auxFloat = proxim[ler];
        proxim[ler] = proxim[posi];
        proxim[posi] = auxFloat;

        auxFloat = amigo[ler];
        amigo[ler] = amigo[posi];
        amigo[posi] = auxFloat;
      }
    }
  }
  int bug[updates];
  for (ler = 0; ler < updates; ler ++)
  {
    scanf("%d", &posi); scanf("%f", &tempo[ler]);
    post[ler] = procura(posi, amigo, friends);
    bug[ler] = posi;
    getchar(); scanf("%[^\n]", frase[ler]);
  }
  for (ler = 0; ler < updates; ler ++)
  {
    for (posi = ler; posi < updates; posi ++)
    {
      if ((proxim[post[ler]] * 0.8) + (tempo[ler] * 0.2) < (proxim[post[posi]] * 0.8) + (tempo[posi] * 0.2))
      {
        auxFloat = proxim[post[ler]];
        proxim[post[ler]] = proxim[post[posi]];
        proxim[post[posi]] = auxFloat;

        auxFloat = tempo[ler];
        tempo[ler] = tempo[posi];
        tempo[posi] = auxFloat;

        strcpy(auxWord, frase[ler]);
        strcpy(frase[ler], frase[posi]);
        strcpy(frase[posi], auxWord);

        auxFloat = post[ler];
        post[ler] = post[posi];
        post[posi] = auxFloat;

        auxFloat = bug[ler];
        bug[ler] = bug[posi];
        bug[posi] = auxFloat;
      }
    }
  }
  for (ler = 0; ler < feed; ler ++)
  {
    printf("%d %s\n", bug[ler], frase[ler]);
  }
  return(0);
}
/*
4
4
1 0.5
3 0.3
2 0.8
0 0.2
5
1 0.9 Estou adorando programar hoje!
1 0.95 Droga, errei. Mas vou tentar mais um pouco.
0 0.71 Eu topo!! Depois a gente estuda
3 0.7 Alguem afim de uma cerveja?
2 0.8 To fora! Prefiro programar
*/
