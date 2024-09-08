#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli maxA = 1e9;
lli a[maxN];

bool match(lli num, bool positive)
{
  if (positive) return num > 0;
  else return num < 0;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    lli ans = 0; bool positive = a[0] > 0;
    lli best;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      best = a[i];
      while (j + 1 < n && match(a[j + 1], positive))
        best = max(best, a[++j]);
      ans += best;
      i = j;
      positive = !positive;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
