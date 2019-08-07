#include <bits/stdc++.h>

int main()
{
  int h1, m1, h2, m2;
  while (scanf("%d %d %d %d", &h1, &m1, &h2, &m2) && !(h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0))
  {
    int sleep = 0;
    while (h1 != h2)
    {
      sleep += 60 - m1;
      h1 ++; h1 %= 24;
      m1 = 0;
    }
    sleep += m2 - m1;

    printf("%d\n", sleep < 0 ? (60 * 23) + (60 + sleep) : sleep);
  }
  return(0);
}