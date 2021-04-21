#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];

int tryAll()
{
  int ans = 0;
  for (int i = 1; i < n; i++)
  {
    lli delta = a[i] - a[i - 1];
    bool used = false;

    lli prv;
    int j = i, usedIdx;
    while (j + 1 < n && (a[j + 1] - a[j] == delta || !used))
    {
      if (a[j + 1] - a[j] != delta)
      {
        used = true, usedIdx = j + 1;
        prv = a[j + 1];
        a[j + 1] = a[j] + delta;
      }

      j++;
    }

    DEBUG printf("%d - %lld - %d - %d\n", i, delta, used, j);

    ans = max(ans, j - i + 2 + (!used && !(i == 1 && j == n - 1)));

    if (used)
    {
      a[usedIdx] = prv;
      i = usedIdx - 1;
    }
    else
      i = j;
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    int ans = tryAll();
    reverse(a, a+n);
    ans = max(ans, tryAll());

    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}