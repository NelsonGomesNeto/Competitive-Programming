#include <stdio.h>
#include <string.h>

struct dic
{
  char word[90];
};

int volta(struct dic p, struct dic x, int v)
{
  while (v >= 0)
  {
    if (p.word[v] != x.word[v])
    {
      return(1);
    }
    v --;
  }
  return(0);
}

int main()
{
  int palavras;
  while (scanf("%d", &palavras) != EOF)
  {
    struct dic w[palavras + 10];
    int ler, tecla; float tempo = 0;
    for (ler = 0; ler < palavras; ler ++)
    {
      getchar();
      scanf("%[^\n]", w[ler].word);
    }
    int maior = 0;
    for (ler = 0; ler < palavras; ler ++)
    {
      if (strlen(w[ler].word) > maior)
      {
        maior = strlen(w[ler].word);
      }
    }
    int se, ch;
    char aux[91];
    /*for (ler = 0; ler < palavras; ler ++)
    {
      for (se = ler; se < palavras; se ++)
      {
        if (strcmp(w[ler].word, w[se].word) > 0)
        {
          strcpy(aux, w[ler].word);
          strcpy(w[ler].word, w[se].word);
          strcpy(w[se].word, aux);
        }
      }
    }*/
    for (ler = 0; ler < palavras; ler ++)
    {
      //printf("%s\n", w[ler].word);
      for (se = 0; se <= maior; se ++)
      {
        if (w[ler].word[se] == '\0')
        {
          w[ler].word[se] = ' ';
        }
      }
    }
    for (ler = 0; ler < palavras; ler ++)
    {
      tecla = 1; int not, unica = 0;
      for (se = 1; se < strlen(w[ler].word);)
      {
        not = 0;
        if (w[ler].word[se] != ' ')
        {
          for (ch = 0; ch < palavras; ch ++)
          {
            if (w[ler].word[se] != w[ch].word[se])
            {
              unica ++;
            }
            if (se < strlen(w[ch].word) && ch != ler)
            {
              if (w[ler].word[se] != w[ch].word[se] && volta(w[ler], w[ch], se - 1) == 0)    //w[ler].word[se - 1] == w[ch].word[se - 1])
              {
                tecla ++;
                se ++;
                not ++;
                break;
              }
            }
            //printf("%c~%d\n", w[ler].word[se], tecla);
          }
          if (unica == palavras - 1)
          {
            break;
          }
        }
        else
        {
          break;
        }
        if (not == 0)
        {
          se ++;
        }
      }
      //printf("%d\n", tecla);
      tempo += tecla;
    }
    tempo /= palavras;
    printf("%.2f\n", tempo);
  }
  return(0);
}
/*
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
qwertyuioqwertyuioqwertyuio
qwertyuioqwertyuioqwertyui
*/
