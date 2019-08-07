#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, x, y; scanf("%d %d %d", &n, &x, &y);
  int best = 1e9, bi;
  for (int i = 0; i < n; i ++)
  {
    int xx, yy, p; scanf("%d %d %d", &xx, &yy, &p);
    int cost = 2*(abs(x - xx) + abs(y - yy)) + p;
    if (cost < best)
      best = cost, bi = i;
  }
  printf("%d %d\n", best, bi + 1);
  return(0);
}