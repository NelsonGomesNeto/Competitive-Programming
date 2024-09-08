#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5 + 1; int n;
int a[maxN], b[maxN];

vector<int> graph[maxN];
bool visited[maxN];
void dfs(int u)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: graph[u])
    dfs(v);
}

const lli mod = 1e9 + 7;
lli fat[maxN + 1], pot[maxN + 1];

int main()
{
  fat[0] = 1;
  pot[0] = 1;
  for (int i = 1; i <= maxN; i++)
  {
    fat[i] = fat[i - 1] * i % mod;
    pot[i] = pot[i - 1] * 2 % mod;
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &b[i]);
      b[i]--;
    }

    for (int i = 0; i < n; i++)
      graph[i].clear(), graph[i].clear(), visited[i] = false;

    for (int i = 0; i < n; i++)
      graph[a[i]].push_back(b[i]);

    int components = 0;
    for (int i = 0; i < n; i++)
      if (!visited[a[i]])
        dfs(a[i]), components++;

    DEBUG printf("\t%d\n", components);

    lli ans = pot[components] % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
