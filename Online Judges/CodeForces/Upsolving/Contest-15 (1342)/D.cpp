#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
map<int, int> cnt;
int c[maxN + 1];
int turn[maxN + 1];

int segtree[4*(maxN + 5)], nil = 0;
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = k + 1)
{
  if (lo > qhi || hi < qlo) return nil;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = k + 1)
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

int main()
{
  int tt = 0;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    memset(segtree, 0, sizeof(segtree));
    cnt.clear();
    if (tt++) printf("------------\n");
    for (int i = 0; i < n; i++)
    {
      int sz; scanf("%d", &sz);
      if (!cnt.count(sz)) cnt[sz] = 0;
      cnt[sz]++;
    }

    for (int i = 0; i < k; i++)
      scanf("%d", &c[i + 1]), turn[i + 1] = 0;

    vector<vector<int>> ans; ans.push_back(vector<int>());
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= k; i++)
      if (cnt[i])
        pq.push({min(c[i], cnt[i]), i});
    int ct = 0;
    while (!cnt.empty() && !pq.empty())
    {
      int i = pq.top().second;
      int toAdd = min(c[i] - max(0, query(i, k + 1)), cnt[i]);
      pq.pop();
      if (cnt[i] == 0) continue;
      if (toAdd <= 0)
      {
        update(k + 1, -(int)ans.back().size());
        ans.push_back(vector<int>());
        pq.push({min(c[i], cnt[i]), i});
        ct++;
        continue;
      }
      if (ct != turn[i])
      {
        turn[i] = ct;
        pq.push({min(c[i] - query(i, k + 1), cnt[i]), i});
        continue;
      }

      for (int j = 0; j < toAdd; j++)
        ans.back().push_back(i);
      cnt[i] -= toAdd;
      update(i, toAdd);
      if (cnt[i] == 0)
        cnt.erase(i);
      else
        pq.push({min(c[i] - query(i, k + 1), cnt[i]), i});
    }

    printf("%d\n", (int)ans.size());
    for (auto &a: ans)
    {
      printf("%d", (int)a.size());
      for (int i: a) printf(" %d", i);
      printf("\n");
    }
  }
  return 0;
}
