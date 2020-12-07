#include <bits/stdc++.h>
using namespace std;
 
const int maxN = 3e5, inf = 1e6; int n;
int a[maxN], b[maxN];
deque<int> pos[maxN + 1];
 
int segtree[4*(maxN + 1)];
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = pos[lo].size() ? pos[lo].front() : inf;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > qhi || hi < qlo) return(inf);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(min(query(qlo, qhi, 2*i, lo, mid), query(qlo, qhi, 2*i + 1, mid + 1, hi)));
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > pos || hi < pos) return;
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  update(pos, value, 2*i, lo, mid), update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}
 
int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) pos[i].clear();
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i ++) scanf("%d", &b[i]);
    build();
 
    bool can = true;
    for (int i = 0; i < n; i ++)
    {
      if (pos[b[i]].empty() || query(0, b[i] - 1) < pos[b[i]].front())
      {
        can = false;
        break;
      }
      pos[b[i]].pop_front();
      update(b[i], pos[b[i]].size() ? pos[b[i]].front() : inf);
    }
 
    printf("%s\n", can ? "YES" : "NO");
  }
	return(0);
}