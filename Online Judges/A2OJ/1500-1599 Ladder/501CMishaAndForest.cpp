#include <bits/stdc++.h>
using namespace std;

const int maxN = 1 << 16; int n, m;
int degree[maxN], s[maxN];
vector<int> graph[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d %d", &degree[i], &s[i]);
  queue<int> q;
  for (int i = 0; i < n; i ++) if (degree[i] == 1) q.push(i);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (degree[u] == 0) continue;
    graph[u].push_back(s[u]), m ++;
    degree[s[u]] --, s[s[u]] ^= u;
    if (degree[s[u]] == 1) q.push(s[u]);
  }
  printf("%d\n", m);
  for (int u = 0; u < n; u ++)
    for (int v: graph[u])
      printf("%d %d\n", u, v);
  return(0);
}