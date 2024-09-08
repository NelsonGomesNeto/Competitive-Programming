#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1 << 20; int n = 1 << 20, q;
lli a[maxN];
set<int> pos;

int main()
{
  while (~scanf("%d", &q))
  {
    fill(a, a+n, -1);
    pos.clear();
    for (int i = 0; i < n; i++) pos.insert(i);

    while (q--)
    {
      int t;
      lli x; scanf("%d %lld", &t, &x);

      if (t == 1)
      {
        auto it = pos.lower_bound(x % n);
        if (it == pos.end())
          it = pos.begin();
        a[*it] = x;
        pos.erase(it);
      }
      else
      {
        printf("%lld\n", a[x % n]);
      }
    }
  }
  return 0;
}