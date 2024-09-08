#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1; int n;
vector<lli> a, uni;
map<lli, int> compress; lli decompress[maxN];

int cnt[maxN], r[maxN], cnt2[maxN];

int segtree[4*maxN];
void update(int pos, int value, int i = 1, int lo = 1, int hi = n)
{
  if (lo == hi)
  {
    segtree[i] += value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
int query(int qlo, int qhi, int i = 1, int lo = 1, int hi = n)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}

int main()
{
  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (tt ++)
    {
      memset(cnt, 0, sizeof(cnt)), memset(cnt2, 0, sizeof(cnt2));
      memset(segtree, 0, sizeof(segtree));
      a.clear(), compress.clear();
    }

    for (int i = 0; i < n; i ++)
    {
      lli aa; scanf("%lld", &aa);
      a.push_back(aa);
    }
    uni = a;
    sort(uni.begin(), uni.end());
    uni.resize(distance(uni.begin(), unique(uni.begin(), uni.end())));
    for (int i = 0; i < uni.size(); i ++)
      compress[uni[i]] = i, decompress[i] = uni[i];
    for (int i = 0; i < n; i ++)
      a[i] = compress[a[i]];

    for (int i = n - 1; i >= 0; i --)
      r[i] = ++ cnt[a[i]];
    for (int i = 0; i < n; i ++)
      update(r[i], 1);

    lli ans = 0;
    for (int i = 0; i < n - 1; i ++)
    {
      cnt2[a[i]] ++;
      update(r[i], -1);
      if (cnt2[a[i]] > 1)
        ans += query(1, cnt2[a[i]] - 1);
    }
    printf("%lld\n", ans);
  }
  return 0;
}