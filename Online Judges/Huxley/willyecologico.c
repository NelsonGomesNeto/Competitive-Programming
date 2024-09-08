#include <stdio.h>

int main()
{
  long long int tree, wood; scanf("%Ld %Ld", &tree, &wood);
  long long int H[tree], ler, super, o, b, aux, mad = 0, desce = 0;
  for (ler = 0; ler < tree; ler ++)
  {
    scanf("%Ld", &H[ler]);
  }
  for (o = 0; o < tree; o ++)
  {
    for (b = o; b < tree; b ++)
    {
      if (H[o] < H[b])
      {
        aux = H[o];
        H[o] = H[b];
        H[b] = aux;
      }
    }
  }
  while (mad < wood)
  {
    //printf("%d\n", H[0]);
    super = H[desce]; mad = 0;
    for (o = 0; o < tree; o ++)
    {
      if (H[o] - super >= 0)
      {
        mad += H[o] - super;
      }
    }
    desce ++;
  }
  printf("%Ld\n", super);
  return(0);
}
