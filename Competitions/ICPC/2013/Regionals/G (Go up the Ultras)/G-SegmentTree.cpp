#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxH = 1e6, inf = 1e9; int n;
int h[maxN], a[maxN], hh[maxN], ultra[maxN], ultraSize, heightsSize;
set<int> heights;
int allHeights[maxH + 1];
bool isUltra[maxN];

int ordinaryMinimumSegtree[4*maxN];
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    ordinaryMinimumSegtree[i] = h[lo];
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  ordinaryMinimumSegtree[i] = min(ordinaryMinimumSegtree[2*i], ordinaryMinimumSegtree[2*i + 1]);
}
int queryMinimum(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return(inf);
  if (lo >= qlo && hi <= qhi) return(ordinaryMinimumSegtree[i]);
  int mid = (lo + hi) >> 1;
  return(min(queryMinimum(qlo, qhi, 2*i, lo, mid), queryMinimum(qlo, qhi, 2*i + 1, mid + 1, hi)));
}

int segtree[4*maxN], nullNode;
int (*f)(int, int);
int minFunc(int a, int b) { return(a < b ? a : b); }
int maxFunc(int a, int b) { return(a > b ? a : b); }

int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = heightsSize - 1)
{
  if (hi < qlo || lo > qhi) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(f(query(qlo, qhi, 2*i, lo, mid), query(qlo, qhi, 2*i + 1, mid + 1, hi)));
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = heightsSize - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = f(segtree[2*i], segtree[2*i + 1]);
}

void reset(int value)
{
  for (int i = 0, end = 4*heightsSize; i < end; i ++)
    segtree[i] = value;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(isUltra, false, sizeof(isUltra)), heights.clear();
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &h[i]);
      heights.insert(h[i]);
    }
    int ii = 0;
    for (int i: heights) allHeights[i] = ii ++;
    for (int i = 0; i < n; i ++) hh[i] = allHeights[h[i]];
    build(), heightsSize = heights.size();

    reset(nullNode = -1), f = maxFunc;
    for (int i = 0; i < n; i ++)
    {
      if (h[i] < 150000) continue;
      int firstHigher = query(hh[i] + 1, heightsSize - 1);
      if (firstHigher != nullNode)
        isUltra[i] = h[i] - queryMinimum(firstHigher, i) >= 150000;
      else
        isUltra[i] = true;
      update(hh[i], i);
    }
    reset(nullNode = inf), f = minFunc;
    for (int i = n - 1; i >= 0; i --)
    {
      if (h[i] < 150000) continue;
      int firstHigher = isUltra[i] ? query(hh[i] + 1, heightsSize - 1) : nullNode;
      if (firstHigher != nullNode)
        isUltra[i] = h[i] - queryMinimum(i, firstHigher) >= 150000;
      update(hh[i], i);
    }

    ultraSize = 0;
    for (int i = 0; i < n; i ++)
      if (isUltra[i])
        ultra[ultraSize ++] = i + 1;
    for (int i = 0; i < ultraSize; i ++)
      printf("%d%c", ultra[i], i < ultraSize - 1 ? ' ' : '\n');
  }
  return(0);
}
