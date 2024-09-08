#include <stdio.h>

struct sorveteiros
{
  int begin, end, will;
};

int main()
{
  int tamanho, quanti;
  scanf("%d %d", &tamanho, &quanti);
  struct sorveteiros s[quanti];
  int ler, comeco = 11111, fim = 0;
  for (ler = 0; ler < quanti; ler ++)
  {
    scanf("%d %d", &s[ler].begin, &s[ler].end);
    if (s[ler].begin < comeco && s[ler].begin >= 0)
    {
      comeco = s[ler].begin;
    }
  }
  int next;
  int o, b, aux;
  for (o = 0; o < quanti; o ++)
  {
    for (b = o; b < quanti; b ++)
    {
      if (s[o].begin > s[b].begin)
      {
        aux = s[o].begin;
        s[o].begin = s[b].begin;
        s[b].begin = aux;
        aux = s[o].end;
        s[o].end = s[b].end;
        s[b].end = aux;
      }
      if (s[o].begin == s[b].begin && s[o].end < s[b].end)
      {
        aux = s[o].begin;
        s[o].begin = s[b].begin;
        s[b].begin = aux;
        aux = s[o].end;
        s[o].end = s[b].end;
        s[b].end = aux;
      }
    }
  }
  for (ler = 0; ler < quanti; ler ++)
  {
    if (ler == 0)
    {
      printf("%d ", comeco);
      next = s[ler].end;
    }
    else
    {
      if (s[ler].begin > next)
      {
        printf("%d\n", next);
        printf("%d ", s[ler].begin);
        if (s[ler].end > next && s[ler].end <= tamanho)
        {
          next = s[ler].end;
        }
      }
      else
      {
        if (s[ler].end > next && s[ler].end <= tamanho)
        {
          next = s[ler].end;
        }
      }
    }
  }
  printf("%d\n", next);
  return(0);
}
