#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4; int n, m, origin, power;
vector<int> graph[maxN];
int dist[maxN];
string getRadiation(int radiation)
{
  if (radiation > n * 2) return("fortissima");
  if (n * 1.5 <= radiation && radiation <= n * 2) return("grave");
  return("leve");
}
struct Person
{
  int radiation;
  string name;
  bool operator<(const Person &p) const { return(radiation < p.radiation || (radiation == p.radiation && name > p.name)); }
  void print()
  {
    printf("Radiacao %s em %s.\n", getRadiation(radiation).c_str(), name.c_str());
  }
};
Person people[maxN];

void bfs()
{
  memset(dist, -1, sizeof(dist)); dist[origin] = 0;
  queue<int> q; q.push(origin);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: graph[u])
      if (dist[v] == -1)
        dist[v] = dist[u] + 1, q.push(v);
  }
  int furthest = 0;
  for (int i = 0; i < n; i ++) furthest = max(furthest, dist[i]);
  for (int i = 0; i < n; i ++)
    people[i].radiation = (furthest - dist[i]) * (n + power);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }
  for (int i = 0; i < n; i ++) cin >> people[i].name;
  scanf("%d %d", &origin, &power); origin --;
  bfs();

  sort(people, people+n);
  reverse(people, people+n);
  for (int i = 0; i < n; i ++)
    people[i].print();

  return(0);
}