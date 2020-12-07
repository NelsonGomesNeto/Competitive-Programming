#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int l, v, lo, hi; scanf("%d %d %d %d", &l, &v, &lo, &hi);
    printf("%d\n",  l / v - hi / v + lo / v - (lo % v == 0));
    // printf("%d\n", (lo - 1) / v + (l - hi) / v + (hi + 1 <= l && (hi + 1) % v == 0) + (lo - 1 > v && (lo - 1) % v == 0));
    // printf("%d %d\n", (lo - 1) / v, (l - hi + 1) / v);
  }
  return(0);
}