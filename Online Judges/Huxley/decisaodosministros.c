#include <stdio.h>

struct projeto
{
  int sim, nao;
};

int main()
{
  int projetos, ministros, run = 1;
  while (scanf("%d %d", &projetos, &ministros) && !(projetos == 0 && ministros == 0))
  {
    struct projeto p[projetos];
    int ler;
    for (ler = 0; ler < projetos; ler ++)
    {
      p[ler].sim = 0; p[ler].nao = 0;
    }
    for (ler = 0; ler < ministros; ler ++)
    {
      int i, votos, ID; char votado;
      scanf("%d", &votos);
      for (i = 0; i < votos; i ++)
      {
        scanf("%d %c", &ID, &votado);
        if (votado == 's')
        {
          p[ID - 1].sim += 1;
        }
        else
        {
          p[ID - 1].nao += 1;
        }
      }
    }
    int possivel = 0;
    for (ler = 0; ler < projetos; ler ++)
    {
      if (p[ler].sim != p[ler].nao)
      {
        possivel ++;
      }
    }
    printf("Caso %d: ", run);
    if (possivel > 0)
    {
      for (ler = 0; ler < projetos; ler ++)
      {
        if (p[ler].sim > p[ler].nao)
        {
          printf("S");
        }
        else if (p[ler].sim < p[ler].nao)
        {
          printf("N");
        }
        else
        {
          printf("?");
        }
      }
    }
    else
    {
      printf("impossivel");
    }
    printf("\n");
    run ++;
  }
  return(0);
}
