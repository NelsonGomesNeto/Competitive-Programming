#include <bits/stdc++.h>

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int problems = 0, timeLeft = 240 - k;
  for (int i = 1; i <= n; i ++)
    if (5 * i <= timeLeft)
    {
      timeLeft -= 5 * i;
      problems ++;
    }

  printf("%d\n", problems);

  return(0);
}