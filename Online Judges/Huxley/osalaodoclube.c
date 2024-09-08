#include <stdio.h>

int main()
{
  int H, L;
  while (scanf("%d %d", &H, &L) && !(H == 0 && L == 0))
  {
    int larg; scanf("%d", &larg); H *= 100; L *= 100;
    int placas; scanf("%d", &placas);
    int tam[placas], base[placas], ler, o, b, aux, menor = 0, quantidade = 0;
    for (ler = 0; ler < placas; ler ++)
    {
      scanf("%d", &tam[ler]);
      tam[ler] *= 100;
    }
    for (o = 0; o < placas; o ++)
    {
      for (b = o; b < placas; b ++)
      {
        if (tam[o] < tam[b])
        {
          aux = tam[o];
          tam[o] = tam[b];
          tam[b] = aux;
        }
      }
    }

    for (o = 0; o < placas; o ++)
    {
      base[o] = tam[o];
    }
    int Hatual, Latual;
    for (Latual = 0, o = 0; Latual < L; o ++) //Tenta com H;
    {
      if (o >= placas)
      {
        break;
      }
      if (tam[o] < H)
      {
        for (b = 0; b < placas; b ++)
        {
          if (tam[o] + tam[b] == H && o != b)
          {
            tam[o] = 0; tam[b] = 0;
            menor += 2;
            Latual += larg;
          }
        }
      }
      else if (tam[o] == H)
      {
        tam[o] = 0;
        menor ++;
        Latual += larg;
      }
    }
    if (Latual == L)
    {
      quantidade = menor;
    }
    for (o = 0; o < placas; o ++)
    {
      tam[o] = base[o];
    }
    menor = 0;
    for (Hatual = 0, o = 0; Hatual < H; o ++) //Tenta com H;
    {
      if (o >= placas)
      {
        break;
      }
      if (tam[o] < L)
      {
        for (b = 0; b < placas; b ++)
        {
          if (tam[o] + tam[b] == L && o != b)
          {
            tam[o] = 0; tam[b] = 0;
            menor += 2;
            Hatual += larg;
          }
        }
      }
      else if (tam[o] == L)
      {
        tam[o] = 0;
        menor ++;
        Hatual += larg;
      }
      //printf("~~%dx%dx%d\n", menor, Hatual, H);
    }
    if (Hatual == H && (menor < quantidade || quantidade == 0))
    {
      quantidade = menor;
    }
    if (quantidade > 0)
    {
      printf("%d\n", quantidade);
    }
    else
    {
      printf("impossivel\n");
    }
  }
}
/*4 5
100
10
1 2 2 2 2 3 3 4 4 5*/
