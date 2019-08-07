#include <bits/stdc++.h>
using namespace std;

const int maxN = 5e4; int n, m;
vector<int> graph[maxN];
int indegree[maxN];

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    graph[u].push_back(v);
    indegree[v] ++;
  }

  vector<int> ans;
  priority_queue<int> q;
  for (int i = 0; i < n; i ++)
    if (!indegree[i])
      q.push(-i);
  while (!q.empty())
  {
    int u = -q.top(); q.pop();
    ans.push_back(u);
    for (int v: graph[u])
      if (!(-- indegree[v]))
        q.push(-v);
  }
  if (ans.size() != n) printf("*\n");
  else for (int i: ans) printf("%d\n", i);

  return(0);
}