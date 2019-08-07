#include <stdio.h>
#include <math.h>

int armstrong(int m, int p)
{
  if (!m) return(0);
  return(pow(m % 10, p) + armstrong(m / 10, p));
}

int main()
{
  int m; scanf("%d", &m);

  int size = ceil(log10(m)) + (pow(10, (int) log10(m)) == m);
  int arms = armstrong(m, size);
  if (arms == m)
    printf("Armstrong\n");
  else
    printf("soma: %d\n", arms);

  return(0);
}