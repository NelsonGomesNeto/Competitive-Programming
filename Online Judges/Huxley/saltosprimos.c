#include <stdio.h>
#include <math.h>

int checkPrimo(int num)
{
  int veri;
  if (num == 2)
  {
    return(1);
  }
  if (num < 2)
  {
    return(0);
  }
  for (veri = 2; veri < sqrt(num) + 1; veri ++)
  {
    if (num % veri == 0)
    {
      return(0);
    }
  }
  return(1);
}

int main()
{
  int menor, maior; scanf("%d %d", &menor, &maior);
  int salto[maior - menor], de, ate, par = 0, primos = 0, big, biganterior = 0, bigJump, aux;
  while (menor <= maior)
  {
    if (checkPrimo(menor) == 1)
    {
      if (par == 0)
      {
        de = menor;
        par ++;
      }
      else
      {
        ate = menor;
        salto[primos] = ate - de;
        //printf("%d\n", salto[primos]);
        de = ate;
        primos ++;
      }
    }
    menor ++;
  }
  primos ++;
  for (menor = 0; menor < primos; menor ++)
  {
    for (maior = menor; maior < primos; maior ++)
    {
      if (salto[menor] > salto[maior])
      {
        aux = salto[menor];
        salto[menor] = salto[maior];
        salto[maior] = aux;
      }
    }
  }
  menor = 0; maior = 0;
  if (primos <= 1)
  {
    printf("-1\n");
    return(0);
  }
  else if (primos == 2)
  {
    printf("%d\n", salto[0]);
    return(0);
  }
  while (menor <= primos / 2)
  {
    big = 1;
    while (salto[menor] == salto[menor + 1])
    {
      //printf("%d~~%d\n", salto[menor], salto[menor + 1]);
      big ++;
      menor ++;
    }
    if (big > biganterior)
    {
      bigJump = salto[menor - 1];
    }
    biganterior = big;
    menor ++;
  }
  if (menor > 0)
  {
    printf("%d\n", bigJump);
  }
  else { printf("-1\n"); }
  return(0);
}
