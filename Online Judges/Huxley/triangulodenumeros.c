#include <stdio.h>
#include <math.h>

int main()
{
  int N, repeat, trian, forma = 1; scanf("%i", &N);
  for (repeat = 1; repeat <= N; repeat ++)
  {
    forma = 0;
    for (trian = repeat; trian > 0; trian --)
    {
      printf("%d", repeat);
    }
    printf("\n");
  }
  return(0);
}
