#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int a, b, k;
struct Pair
{
  int boy, girl;
  bool operator<(const Pair &other) const { return boy < other.boy || (boy == other.boy && girl < other.girl); }
};
Pair pairs[maxN];
int cnt[2][maxN];
map<Pair, int> cntPair;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &a, &b, &k);
    cntPair.clear();
    for (int i = 0; i < a; i++)
      cnt[0][i] = 0;
    for (int i = 0; i < b; i++)
      cnt[1][i] = 0;

    for (int i = 0; i < k; i++)
    {
      scanf("%d", &pairs[i].boy);
      pairs[i].boy--;
      cnt[0][pairs[i].boy]++;
    }
    for (int i = 0; i < k; i++)
    {
      scanf("%d", &pairs[i].girl);
      pairs[i].girl--;
      cnt[1][pairs[i].girl]++;
    }
    for (int i = 0; i < k; i++)
    {
      if (!cntPair.count(pairs[i]))
        cntPair[pairs[i]] = 0;
      cntPair[pairs[i]]++;
    }

    lli ans = 0;
    for (int i = 0; i < k; i++)
    {
      ans += k + cntPair[pairs[i]] - cnt[0][pairs[i].boy] - cnt[1][pairs[i].girl];
    }
    printf("%lld\n", ans >> 1LL);
  }
  return 0;
}
