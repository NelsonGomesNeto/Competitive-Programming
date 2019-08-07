#include <stdio.h>

int calibrate(int t, int flip, int n)
{
  if (n == 0)
    return(t);
  if (flip)
    return(calibrate(t + 3, 1 - flip, n - 1));
  else
    return(calibrate(t + (t % 5), 1 - flip, n - 1));
}
int main()
{
  int t, n;
  scanf("%d %d", &t, &n);
  printf("%d\n", calibrate(t, 1, n));
  return(0);
}