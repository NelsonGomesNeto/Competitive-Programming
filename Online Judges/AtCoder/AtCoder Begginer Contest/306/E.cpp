#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5;
int n, k, q;
lli a[maxN];

int main()
{
  while (~scanf("%d %d %d", &n, &k, &q))
  {
    fill(a, a + n, 0);

    lli ans = 0;
    set<pair<lli, int>> bigPq, outsidePq;
    for (int i = 0; i < k; ++i)
      bigPq.insert(make_pair(0LL, i));
    for (int i = k; i < n; ++i)
      outsidePq.insert(make_pair(0LL, i));

    for (int i = 0; i < q; ++i)
    {
      int x;
      lli y;
      scanf("%d %lld", &x, &y);
      --x;

      auto bit = bigPq.find(make_pair(a[x], x));
      if (bit != bigPq.end())
      {
        bigPq.erase(bit);
        bigPq.insert(make_pair(y, x));
        ans += y - a[x];
      }
      else
      {
        auto oit = outsidePq.find(make_pair(a[x], x));
        assert(oit != outsidePq.end());
        outsidePq.erase(oit);
        outsidePq.insert(make_pair(y, x));
      }

      if (!outsidePq.empty() && !bigPq.empty() && outsidePq.rbegin()->first > bigPq.begin()->first)
      {
        ans -= bigPq.begin()->first;
        ans += outsidePq.rbegin()->first;

        auto o = prev(outsidePq.end());
        auto b = bigPq.begin();
        outsidePq.insert(*b), bigPq.insert(*o);
        outsidePq.erase(o), bigPq.erase(b);
      }

      a[x] = y;

      printf("%lld\n", ans);
      DEBUG
      {
        for (auto [v, i] : bigPq)
          printf("\tbig: %d %d\n", v, i);
        for (auto [v, i] : outsidePq)
          printf("\tout: %d %d\n", v, i);
      }
    }
  }
  return 0;
}
