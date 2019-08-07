#include <bits/stdc++.h>
using namespace std;

int n, l, lantern[(int) 1e3];

int main()
{
  scanf("%d %d", &n, &l);
  for (int i = 0; i < n; i ++)
    scanf("%d", &lantern[i]);

  sort(lantern, lantern + n);

  double best = max(lantern[0] - 0, l - lantern[n - 1]);
  for (int i = 1; i < n; i ++)
  {
    double d = (lantern[i] - lantern[i - 1]) / 2.0;
    if (d > best) best = d;
  }

  printf("%.16lf\n", best);

  return(0);
}