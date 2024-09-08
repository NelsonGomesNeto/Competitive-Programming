#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

/* Tutorial:
  For each bit, iterate through the queries:
    if (q[j] requires i-th bit):
      in[q[j].lo] ++, out[q[j].hi] ++
    now = 0
    for j in [0, n - 1]
      now += in[j]
      ans[j] = now > 0 ? 1 << i : 0
      now -= out[j]
  If it's possible, ans holds the answer
  To test if it's valid: build a segtree and test each query
*/

const int maxN = 1e5, maxBit = 30; int n, m;
const lli allSet = (1 << 30) - 1;
int constraints[maxN][3];
int ans[maxN];
int in[maxBit][maxN], out[maxBit][maxN];

int segtree[4*maxN], nullNode = (1 << maxBit) - 1;
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = ans[lo];
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] & segtree[2*i + 1];
}
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return nullNode;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) & query(qlo, qhi, 2*i + 1, mid + 1, hi);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &constraints[i][0], &constraints[i][1], &constraints[i][2]);
    constraints[i][0] --, constraints[i][1] --;
  }

  for (int i = 0; i < maxBit; i ++)
  {
    for (int j = 0; j < m; j ++)
      if (constraints[j][2] & (1 << i))
        in[i][constraints[j][0]] ++, out[i][constraints[j][1]] ++;
    for (int j = 0, now = 0; j < n; j ++)
    {
      now += in[i][j];
      ans[j] |= now ? 1 << i : 0;
      now -= out[i][j];
    }
  }
  build();

  bool valid = true;
  for (int i = 0; i < m; i ++)
    if (constraints[i][2] != query(constraints[i][0], constraints[i][1]))
      valid = false;
  if (!valid) printf("NO\n");
  else
  {
    printf("YES\n");
    for (int i = 0; i < n; i ++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}