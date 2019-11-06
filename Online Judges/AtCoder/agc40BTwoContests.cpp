#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli inf = 1e18;
struct Problem
{
  lli l, r;
  void read() { scanf("%lld %lld", &l, &r); }
};
Problem problems[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    lli maxL = -inf, minR = inf;
    for (int i = 0; i < n; i ++)
    {
      problems[i].read();
      maxL = max(maxL, problems[i].l);
      minR = min(minR, problems[i].r);
    }

    lli ans = 0;
    // maxL and minR will have to either be in the same contest or not

    // if they're in the same contest:
    for (int i = 0; i < n; i ++)
      ans = max(ans, max(0LL, minR - maxL + 1) + problems[i].r - problems[i].l + 1);

    // if they're not in the same contest:
    vector<pair<lli, lli>> t;
      // If a problem is in maxL group: max(0, problems[i].r - maxL + 1), let's call this a
      // If a problems is in minR group: max(0, minR - problems[i] + 1), let's call this b
      // sort the pairs (a, b) ascending by a and descending by b, let's call the vector of pairs t
      // now find the index i in which maximizes: min(t[0 : i].b) + min(t[i + 1 : n - 1].a)
    for (int i = 0; i < n; i ++)
      t.push_back({max(0LL, problems[i].r - maxL + 1), -max(0LL, minR - problems[i].l + 1)});
    sort(t.begin(), t.end());

    lli curr = -t[0].second;
    for (int i = 1; i < n; i ++)
    {
      ans = max(ans, curr + t[i].first);
      curr = min(curr, -t[i].second);
    }
    printf("%lld\n", ans);
  }

  return 0;
}