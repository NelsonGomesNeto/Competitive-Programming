#include <stdio.h>

int main()
{
  long long int l1, r1, l2, r2, k;
  scanf("%Ld %Ld %Ld %Ld %Ld", &l1, &r1, &l2, &r2, &k);
  if (r1 >= l2)
  {
    long long int juntos = (r1 - l2) + 1;
    int naim = 0;
    if (r2 < r1)
    {
      naim ++;
      juntos -= r1 - r2;
    }
    if (k <= r1 && k >= l2 && k >= l1 && k <= r2)
    {
      juntos --;
    }
    printf("%Ld", juntos);
  }
  else
  {
    printf("0");
  }
  return(0);
}
