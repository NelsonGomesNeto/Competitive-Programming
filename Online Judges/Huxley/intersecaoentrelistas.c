#include <stdio.h>

int main()
{
  int ler, check, listaA[30], listaB[30], unico[30], tam = 0, unik = 0, ja = 0, already[30], all;
  int aux;
  for (ler = 0; ler < 20; ler ++)
  {
    scanf("%d", &listaA[ler]);
  }
  for (ler = 0; ler < 20; ler ++)
  {
    scanf("%d", &listaB[ler]);
  }
  for (ler = 0; ler < 20; ler ++)
  {
    for (check = 0; check < 20; check ++)
    {
      if (listaA[ler] == listaB[check])
      {
        unico[tam] = listaA[ler];
        tam ++;
        check = 20;
      }
    }
  }
  //printf("%d~~~~~~~~\n", tam);
  ler = 0; check = 0;
  while (ler < tam)
  {
    check = 0;
    while (check < tam)
    {
      if (unico[ler] < unico[check])
      {
        //printf("foi%d~%d~", ler, check);
        aux = unico[ler];
        unico[ler] = unico[check];
        unico[check] = aux;
      }
      check ++;
    }
    ler ++;
  }
  for (ler = 0; ler < tam; ler ++)
  {
    if (ler == 0)
    {
      printf("%d\n", unico[ler]);
      already[unik] = unico[ler];
      unik ++;
    }
    else
    {
      for (check = 0; check < unik; check ++)
      {
        if (unico[ler] == already[check])
        {
          /*printf("%d\n", unico[ler]);
          already[unik] = unico[ler];
          unik ++;*/
          check = unik;
        }
      }
      if (check == unik)
      {
        printf("%d\n", unico[ler]);
        already[unik] = unico[ler];
        unik ++;
      }
    }
  }
  if (unik == 0)
  {
    printf("VAZIO\n");
  }
  return(0);
}
