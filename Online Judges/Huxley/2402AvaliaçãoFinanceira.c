#include <stdio.h>

typedef struct Interval { int start, end, sum; } Interval;

int main()
{
  int n, i, x, prev = -1; scanf("%d", &n);
  Interval best, now; best.sum = -1, now.start = 1, now.sum = 0;
  for (i = 0; i < n; i ++)
  {
    scanf("%d", &x);
    now.end = i + 1;
    if (x > prev) now.sum += x;
    else now.start = i + 1, now.sum = x;
    if (now.sum > best.sum) best = now;
    prev = x;
  }
  printf("%d %d %d\n", best.start, best.end, best.sum);

  return(0);
}