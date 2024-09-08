#include <stdio.h>

int main()
{
  int N, repeat; scanf("%i", &N);
  int array[N];
  for (repeat = 0; repeat < N; repeat ++)
  {
    scanf("%i", &array[repeat]);
  }
  for (repeat = 0; repeat < N; repeat ++)
  {
    printf("%i\n", (2 * array[repeat]));
  }
  return(0);
}
