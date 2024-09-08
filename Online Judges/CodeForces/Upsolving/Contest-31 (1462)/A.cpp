#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int lo = 0, hi = n - 1, turn = 0;
    int ans[n], i = 0;
    while (lo <= hi)
    {
      ans[i++] = a[turn ? hi : lo];
      if (turn) hi--;
      else lo++;
      turn = !turn;
    }
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
