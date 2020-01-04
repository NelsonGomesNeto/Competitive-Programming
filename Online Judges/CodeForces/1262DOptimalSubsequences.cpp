#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
map<lli, vector<int>> pos;
map<int, vector<pair<int, int>>> queries;
lli ans[maxN];

int segtree[4*maxN];
void update(int pos, int value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}

int binarySearch(int target, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (query(0, mid) <= target)
      lo = mid;
    else
      hi = mid - 1;
  }
  DEBUG printf("%d %d %d %lld\n", target, lo, query(0, lo), a[lo]);
  return lo + (query(0, lo) <= target);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(segtree, 0, sizeof(segtree));
    pos.clear(), queries.clear();
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      pos[a[i]].push_back(i);
    }

    int q; scanf("%d", &q);
    for (int qq = 0; qq < q; qq ++)
    {
      int k, p; scanf("%d %d", &k, &p);
      queries[k].push_back({p, qq});
    }
    for (auto &qq: queries)
      sort(qq.second.begin(), qq.second.end());

    auto it = pos.end() --;
    for (int k = 0, s = 1; k < n; it --)
      for (int p = 0; p < it->second.size(); p ++, k ++, s ++)
      {
        update(it->second[p], 1); 
        if (queries.count(s))
          for (auto qp: queries[s])
            ans[qp.second] = a[binarySearch(qp.first - 1)];
      }

    for (int i = 0; i < q; i ++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}
