#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, q;
lli a[maxN];
int kidkin[maxN];
multiset<lli> kinder[maxN];

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    for (int i = 0; i < maxN; i++) kinder[i].clear();
    for (int i = 0; i < n; i++)
    {
      int b; scanf("%lld %d", &a[i], &b); b--;
      kinder[b].insert(a[i]), kidkin[i] = b;
    }

    multiset<lli> curr;
    for (int i = 0; i < maxN; i++)
      if (!kinder[i].empty())
        curr.insert(*kinder[i].rbegin());

    while (q--)
    {
      int i, d; scanf("%d %d", &i, &d); i--, d--;
      if (kidkin[i] != d)
      {
        lli biggestPrv = *kinder[kidkin[i]].rbegin();
        auto it = kinder[kidkin[i]].find(a[i]);
        if (it != kinder[kidkin[i]].end()) kinder[kidkin[i]].erase(it);
        auto it2 = curr.find(biggestPrv);
        if (it2 != curr.end()) curr.erase(it2);
        if (!kinder[kidkin[i]].empty()) curr.insert(*kinder[kidkin[i]].rbegin());

        biggestPrv = kinder[d].empty() ? -1 : *kinder[d].rbegin();
        kinder[d].insert(a[i]);
        auto it3 = curr.find(biggestPrv);
        if (it3 != curr.end()) curr.erase(it3);
        curr.insert(*kinder[d].rbegin());

        kidkin[i] = d;
      }
      printf("%lld\n", *curr.begin());
    }
  }
  return 0;
}