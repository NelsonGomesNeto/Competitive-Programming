#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; lli l; int q;
vector<lli> xs;
struct Query {
  int c; lli x;
  void read() { scanf("%d %lld", &c, &x); xs.push_back(x); }
};
Query queries[maxN];
bool has[maxN + 2];

lli compress(lli x)
{
  return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

int main()
{
  while (~scanf("%lld %d", &l, &q))
  {
    xs.clear();
    xs.push_back(0);
    xs.push_back(l);
    for (int i = 0; i < q; i++)
      queries[i].read();
    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

    for (int i = 0; i < xs.size(); i++) has[i] = false;
    has[0] = has[xs.size() - 1] = true;
    set<lli> cuts, ncuts;
    cuts.insert(xs[0]), cuts.insert(xs.back());
    ncuts.insert(-xs[0]), ncuts.insert(-xs.back());

    for (int i = 0; i < q; i++)
    {
      lli cx = compress(queries[i].x);
      if (queries[i].c == 1)
        has[cx] = true, cuts.insert(queries[i].x), ncuts.insert(-queries[i].x);
      else
      {
        lli l = -*ncuts.upper_bound(-queries[i].x), r = *cuts.upper_bound(queries[i].x);
        lli ans = r - l;
        // l = compress(l), r = compress(r);
        // lli ans = xs[r] - xs[l];
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}