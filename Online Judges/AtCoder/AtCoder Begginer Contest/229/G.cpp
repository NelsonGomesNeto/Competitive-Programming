#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
char s[maxN + 1];
vector<int> a, b;
lli acc[maxN + 1];

bool can(int x)
{
  for (int i = 0; i + x - 1 < b.size(); i++)
  {
    int mid = b[i + (x >> 1)];
    int l = lower_bound(b.begin(), b.end(), mid) - b.begin(), r = prev(upper_bound(b.begin(), b.end(), mid)) - b.begin();
    lli below = abs((lli)(l - i) * mid - (acc[l] - acc[i]));
    lli above = abs((lli)(i + x - 1 - r) * mid - (acc[i + x] - acc[r + 1]));
    if (below + above <= k)
      return true;
  }
  return false;
}

int main()
{
  while (~scanf(" %s", s))
  {
    scanf("%lld", &k);
    n = strlen(s);

    a.clear();
    for (int i = 0; i < n; i++)
      if (s[i] == 'Y')
        a.push_back(i);
    b.clear();
    for (int i = 0; i < a.size(); i++)
    {
      b.push_back(a[i] - i);
      acc[i + 1] = acc[i] + b.back();
    }

    int lo = 0, hi = a.size();
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }
    printf("%d\n", lo);
  }
  return 0;
}