#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5; int n, k;
vector<int> tree[maxN];

bool visited[maxN], onqueue[maxN]; int indegree[maxN];
int totalPerLevel[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    k = min(n, k - 1);

    for (int i = 0; i < n; i++) tree[i].clear(), visited[i] = onqueue[i] = false, indegree[i] = totalPerLevel[i] = 0;
    totalPerLevel[n] = 0;

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
      indegree[u]++, indegree[v]++;
    }

    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
      if (indegree[i] == 1)
        q.push(make_pair(i, 0)), onqueue[i] = true;
    while (!q.empty())
    {
      int u = q.front().first, l = q.front().second; q.pop();
      totalPerLevel[l]++;

      for (int v: tree[u])
        if (!onqueue[v] && --indegree[v] == 1)
          q.push(make_pair(v, l + 1)), onqueue[v] = true;
    }

    if (n == 1) totalPerLevel[0] = 1;

    for (int i = 1; i <= n; i++)
      totalPerLevel[i] += totalPerLevel[i - 1];

    assert(totalPerLevel[n] <= n);
    printf("%d\n", n - totalPerLevel[k]);
  }
  return 0;
}
