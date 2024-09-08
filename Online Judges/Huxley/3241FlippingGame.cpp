#include <bits/stdc++.h>
using namespace std;

const int maxN = 5e3;
int n;

int a[maxN];
int acc[maxN + 1];

int sum(int lo, int hi)
{
  if (lo < 0 || hi >= n) return 0;
  return acc[hi + 1] - acc[lo];
}

int sumWithout(int lo, int hi)
{
  return sum(0, lo - 1) + ((hi - lo + 1) - sum(lo, hi)) + sum(hi + 1, n - 1);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);

    acc[0] = 0;
    for (int i = 0; i < n; ++i)
      acc[i + 1] = acc[i] + a[i];

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = i; j < n; ++j)
        ans = max(ans, sumWithout(i, j));
    printf("%d\n", ans);
  }
  return 0;
}
