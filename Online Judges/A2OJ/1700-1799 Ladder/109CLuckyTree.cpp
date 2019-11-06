#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<pair<int, int>> tree[maxN];
bool isLucky(int num)
{
  while (num)
  {
    if (num % 10 != 4 && num % 10 != 7)
      return false;
    num /= 10;
  }
  return true;
}

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
lli setSize(int u) { return -parent[root(u)]; }

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d", &n);
  for (int i = 1; i < n; i ++)
  {
    int u, v, w; scanf("%d %d %d", &u, &v, &w); u --, v --;
    if (!isLucky(w)) merge(u, v);
  }

  lli ans = n <= 2 ? 0 : (lli) n * (n - 1LL) * (n - 2LL), allRemoved = 0;
  DEBUG printf("originally: %lld\n", ans);
  for (int i = 0; i < n; i ++)
    if (parent[i] < -1)
    {
      lli removed = ((lli)n - setSize(i)) * 2LL * setSize(i) * (setSize(i) - 1LL);
      if (setSize(i) >= 3) removed += setSize(i) * (setSize(i) - 1LL) * (setSize(i) - 2LL);
      DEBUG printf("%d %lld - %lld\n", i, setSize(i), removed);
      ans -= removed;
      allRemoved += removed;
    }
  DEBUG printf("end: %lld\n", allRemoved);
  printf("%lld\n", ans);

  return 0;
}