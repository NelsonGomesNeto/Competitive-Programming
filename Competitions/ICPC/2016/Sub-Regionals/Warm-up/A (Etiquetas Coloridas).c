#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned long long int R, G, B;
  scanf("%Lx\n%Lx\n%Lx", &R, &G, &B);

  unsigned long long int pri = R / G, sec = G / B;
  unsigned long long int total = 1 + (pri * pri) + ((pri * sec) * (pri * sec));

  printf("%Lx\n", total);

  return(0);
}
//179841
