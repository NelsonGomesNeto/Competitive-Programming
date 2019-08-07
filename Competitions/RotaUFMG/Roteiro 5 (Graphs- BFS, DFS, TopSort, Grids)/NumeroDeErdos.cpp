#include <bits/stdc++.h>
using namespace std;

void printGraph(vector<int> graph[], int p)
{
  for (int i = 0; i < p; i ++)
  {
    printf("%d", i);
    for (auto j: graph[i])
      printf(" -> %d", j);
    printf("\n");
  }
}

void bfs(vector<int> graph[], int source, int dist[])
{
  deque<pair<int, int> > queue;
  queue.push_back({source, 0});
  while (!queue.empty())
  {
    int u = queue.front().first, d = queue.front().second; queue.pop_front();
    if (dist[u] != -1) continue;
    dist[u] = d;
    for (auto v: graph[u])
      queue.push_back({v, d + 1});
  }
}

int main()
{
  int a, t = 0;
  while (scanf("%d", &a) && a)
  {
    if (t ++) printf("\n");
    getchar();
    map<pair<string, string>, int> people;
    char s[100], ss[100], end;
    int connections[a][101], p = 0, erdos = -1;
    for (int i = 0; i < a; i ++)
    {
      int j = 0;
      while (scanf("%s %s%c", s, ss, &end))
      {
        ss[strlen(ss) - 1] = '\0';
        //printf("%s %s\n", s, ss);
        if (!people.count({ss, s}))
        {
          p ++;
          people[{ss, s}] = p - 1;
          if (!strcmp(s, "P.") && !strcmp(ss, "Erdos")) erdos = p - 1;
        }
        connections[i][++ j] = people[{ss, s}];
        if (end == '\n') break;
      }
      connections[i][0] = j;
    }

    vector<int> graph[p];
    for (int i = 0; i < a; i ++)
      for (int j = 1; j <= connections[i][0]; j ++)
        for (int k = 1; k <= connections[i][0]; k ++)
          if (j != k)
            graph[connections[i][k]].push_back(connections[i][j]);

    int dist[p]; memset(dist, -1, sizeof(dist));
    if (erdos != -1) bfs(graph, erdos, dist);
    printf("Teste %d\n", t);
    for (auto i: people)
    {
      if (i.first.first == "Erdos" && i.first.second == "P.") continue;
      cout << i.first.second << " " << i.first.first << ": ";
      if (dist[people[i.first]] == -1) printf("infinito\n");
      else printf("%d\n", dist[people[i.first]]);
    }
  }
  return(0);
}