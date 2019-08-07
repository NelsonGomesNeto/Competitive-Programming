#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 7555; int n;
int alibis[maxN];
int cited[maxN], noAlibis, suspects;
bool suspicious[maxN], selfAlibi[maxN];
vector<int> graph[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt ++)
  {
    scanf("%d", &n);
    memset(alibis, 0, sizeof(alibis)), memset(suspicious, false, sizeof(suspicious)), memset(selfAlibi, false, sizeof(selfAlibi));
    for (int i = 0; i < n; i ++) graph[i].clear();

    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &cited[i]); cited[i] --;
      if (i == cited[i])
      {
        selfAlibi[i] = true;
        continue;
      }
      if (cited[i] != -1) alibis[cited[i]] ++, graph[i].push_back(cited[i]);
    }

    queue<int> q;
    noAlibis = 0;
    for (int i = 0; i < n; i ++)
      if (!alibis[i])
        noAlibis += !selfAlibi[i], suspicious[i] = true, q.push(i);

    while (!q.empty())
    {
      int u = q.front(); q.pop();
      for (int v: graph[u])
        if (-- alibis[v] == 0)
          suspicious[v] = true, q.push(v);
    }

    suspects = 0;
    for (int i = 0; i < n; i ++) suspects += suspicious[i];
    printf("Caso #%d: %d %d\n", tt, noAlibis, suspects);
  }
  return(0);
}