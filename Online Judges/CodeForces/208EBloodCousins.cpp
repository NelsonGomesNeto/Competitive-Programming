#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, logn;
vector<int> tree[maxN], roots, levelIn[maxN];
int level[maxN], ancestor[maxN][maxLog], in[maxN], out[maxN], now = 0;
void dfs(int u)
{
  in[u] = now ++;
  levelIn[level[u]].push_back(in[u]);
  for (int v: tree[u])
  {
    level[v] = level[u] + 1, ancestor[v][0] = u;
    dfs(v);
  }
  out[u] = now ++;
}
void build()
{
  for (int i: roots)
  {
    level[i] = ancestor[i][0] = 0;
    dfs(i);
  }
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int kthAncestor(int u, int k)
{
  for (int i = 0; k; k >>= 1, i ++)
    if (k & 1) u = ancestor[u][i];
  return(u);
}

int binSearch(vector<int>& array, int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] < target ? lo + 1 : lo);
  int mid = (lo + hi) >> 1;
  if (array[mid] >= target) return(binSearch(array, lo, mid, target));
  return(binSearch(array, mid + 1, hi, target));
}

int query(int u, int p)
{
  if (level[u] < p) return(0);
  int anc = kthAncestor(u, p);
  int lo = binSearch(levelIn[level[u]], 0, levelIn[level[u]].size() - 1, in[anc]);
  int hi = binSearch(levelIn[level[u]], 0, levelIn[level[u]].size() - 1, out[anc]);
  // printf("(%d, in %d, out %d) %d %d\n", anc, in[anc], out[anc], lo, hi);
  // for (int i = 0; i < levelIn[level[u]].size(); i ++) printf("%d%c", levelIn[level[u]][i], i < levelIn[level[u]].size() - 1 ? ' ' : '\n');
  return(hi - lo - 1);
}

int main()
{
  scanf("%d", &n); logn = ceil(log2(n));
  for (int i = 0; i < n; i ++)
  {
    int u; scanf("%d", &u); u --;
    if (u == -1) roots.push_back(i);
    else tree[u].push_back(i);
  }
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    int u, p; scanf("%d %d", &u, &p); u --;
    printf("%d ", query(u, p));
  } printf("\n");
  return(0);
}
