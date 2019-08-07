#include <stdio.h>

int main()
{
  int paises, moda; scanf("%d %d", &paises, &moda);
  int pais[paises + 100][100], oPais[paises + 100], ler, ouro, prata, bronze;
  int o, b, i, j, n, m, aux, all, igual;
  for (ler = 0; ler < moda; ler ++)
  {
    for (ouro = 0; ouro < paises + 1; ouro ++)
    {
      pais[ler][ouro] = 0;
      oPais[ouro] = ouro;
    }
  }
  for (ler = 0; ler < moda; ler ++)
  {
    scanf("%d %d %d", &ouro, &prata, &bronze);
    pais[ouro - 1][0] ++;
    pais[prata - 1][1] ++;
    pais[bronze - 1][2] ++;
  }
  for (o = 0; o < paises; o ++)
  {
    for (b = o + 1; b < paises; b ++)
    {
      if (pais[o][0] < pais[b][0])
      {
        for (i = 0; i < 3; i ++)
        {
          aux = pais[o][i];
          pais[o][i] = pais[b][i];
          pais[b][i] = aux;
        }
        aux = oPais[o];
        oPais[o] = oPais[b];
        oPais[b] = aux;
      }
      else if (pais[o][0] == pais[b][0])
      {
        if (pais[o][1] < pais[b][1])
        {
          for (i = 0; i < 3; i ++)
          {
            aux = pais[o][i];
            pais[o][i] = pais[b][i];
            pais[b][i] = aux;
          }
          aux = oPais[o];
          oPais[o] = oPais[b];
          oPais[b] = aux;
        }
        else if (pais[o][1] == pais[b][1])
        {
          if (pais[o][2] < pais[b][2])
          {
            for (i = 0; i < 3; i ++)
            {
              aux = pais[o][i];
              pais[o][i] = pais[b][i];
              pais[b][i] = aux;
            }
            aux = oPais[o];
            oPais[o] = oPais[b];
            oPais[b] = aux;
          }
          else if (pais[o][2] == pais[b][2])
          {
            if (oPais[o] > oPais[b])
            {
              for (i = 0; i < 3; i ++)
              {
                aux = pais[o][i];
                pais[o][i] = pais[b][i];
                pais[b][i] = aux;
              }
              aux = oPais[o];
              oPais[o] = oPais[b];
              oPais[b] = aux;
            }
          }
        }
      }
    }
  }
  for (ouro = 0; ouro < paises; ouro ++)
  {
    printf("%d\n", oPais[ouro] + 1);
  }
  return(0);
}
