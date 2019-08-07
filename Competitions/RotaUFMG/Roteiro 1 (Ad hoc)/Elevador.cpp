#include <bits/stdc++.h>

int main()
{
  int n, c, now = 0, exceed = 0; scanf("%d %d", &n, &c);

  while (n -- > 0)
  {
    int s, e; scanf("%d %d", &s, &e);
    now += e;
    now -= s; if (now < 0) now = 0;
    if (now > c)
      exceed = 1;
  }

  printf("%s\n", exceed ? "S" : "N");

  return(0);
}