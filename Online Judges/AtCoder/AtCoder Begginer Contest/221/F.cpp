#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;
const lli mod = 998244353;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

const int maxN = 2e5; int n;
vector<int> tree[maxN];

int dist[maxN], bdist[maxN], adist[maxN];
void bfs(int source = 0)
{
  for (int i = 0; i < n; i++) dist[i] = -1;
  dist[source] = 0;
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: tree[u])
      if (dist[v] == -1)
        q.push(v), dist[v] = dist[u] + 1;
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    bfs(0);
    int b = max_element(dist, dist+n) - dist;
    bfs(b);
    memcpy(bdist, dist, sizeof(dist));
    int a = max_element(dist, dist+n) - dist;
    bfs(a);
    memcpy(adist, dist, sizeof(dist));

    int aCnt = 0, aMaxDist = *max_element(adist, adist+n);
    int bCnt = 0, bMaxDist = *max_element(bdist, bdist+n);
    vector<int> as, bs;
    int intersections = 0;

    for (int i = 0; i < n; i++)
      if (adist[i] == aMaxDist && bdist[i] != bMaxDist)
        aCnt++, as.push_back(i);
    for (int i = 0; i < n; i++)
    {
      if (bdist[i] == bMaxDist && adist[i] != aMaxDist)
        bCnt++, bs.push_back(i);
      if (bdist[i] == bMaxDist && adist[i] == aMaxDist)
        intersections++;
    }

    DEBUG printf("\t%d %d %d\n", aCnt, bCnt, intersections);

    lli ans = modPow(2, aCnt - 1) * modPow(2, bCnt - 1) % mod;
    if (intersections)
    {
      ans = ans * modPow(2, intersections) % mod;
      ans = (ans + intersections * modPow(2, aCnt + bCnt - 1) % mod) % mod;
    }

    // ans = modPow(2, aCnt - 1 + bCnt - 1));
    printf("%lld\n", ans);
  }
  return 0;
}