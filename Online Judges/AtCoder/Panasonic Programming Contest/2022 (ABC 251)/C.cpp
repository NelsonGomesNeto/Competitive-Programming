#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxS = 10; int n;
char ss[maxS + 1];
struct Poem
{
  string s; lli t;
};
unordered_set<string> has;
Poem ps[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    has.clear();
    priority_queue<pair<lli, int>> pq;
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s %lld", ss, &ps[i].t);
      ps[i].s = string(ss);
      if (!has.count(ps[i].s))
        pq.push({ps[i].t, -i});

      has.insert(ps[i].s);
    }

    int ans = -pq.top().second;
    printf("%d\n", ans + 1);
  }
  return 0;
}
