#include <stdio.h>
#include <string.h>

int main()
{
  int lixo1, lixo2, ler, posi = 0;
  while (scanf("%d %d", &lixo1, &lixo2) && !(lixo1 == 0 && lixo2 == 0))
  {
    char song[9999], plagio[9999];
    for (ler = 0; ler < 9999; ler ++)
    {
      song[ler] = '\0';
      plagio[ler] = '\0';
    }
    getchar(); scanf("%[^\n]", song);
    getchar(); scanf("%[^\n]", plagio);
    plagio[strlen(plagio)] = ' ';
    for (ler = 0; ler < strlen(song); ler ++)
    {
      if (plagio[posi] == song[ler])
      {
        for (posi = 1; posi < strlen(plagio); posi ++)
        {
          if (plagio[posi] != song[ler + posi])
          {
            break;
          }
        }
      }
      if (posi == strlen(plagio))
      {
        printf("S\n");
        break;
      }
      posi = 0;
    }
    //printf("%d~~~~\n", posi);
    if (ler == strlen(song))
    {
      printf("N\n");
    }
  }
  return(0);
}
