#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4, maxV = 3e4 + 2, inf = 1e9; int n;
map<string, int> partyId, personId, clubId;
vector<string> partyName, personName, clubName;
vector<int> personParty;
vector<vector<int>> personClubs, partyPeople;
// n == party amount, k = people amout, m = club amount
// source (0) -[clubs / 2 - 1]> parties (1 : n) -[1]> people (n + 1 : n + k) -[1]> clubs (n + k + 1 : n + k + m) -[1]> sink (n + m + k + 1)
int source = 0, sink, vertices;
int ptr[maxV], level[maxV];
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source), level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return level[sink] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == sink || !flow) return flow;
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return delivered;
    }
  }
  return 0;
}
int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs()) maxFlow += flow;
  }
  return maxFlow;
}

bool readString(char s[])
{
  char c; int i = 0;
  while (true)
  {
    if (scanf("%c", &c) == EOF || c == ' ' || c == '\n')
      return i > 0;
    s[i ++] = c;
  }
  s[i] = '\0';
  return true;
}
bool readPerson()
{
  char s[100] = "", sep;
  if (!readString(s)) return false;
  string a = s;
  personName.push_back(a);
  personId[a] = personId.size();

  scanf("%s", s);
  a = s;
  if (!partyId.count(a))
  {
    partyName.push_back(a), partyPeople.push_back(vector<int>());
    partyId[a] = partyId.size();
  }
  personParty.push_back(partyId[a]);
  partyPeople[partyId[a]].push_back(personId.size() - 1);

  personClubs.push_back(vector<int>());
  while (scanf("%c", &sep) != EOF && sep == ' ')
  {
    scanf("%s", s);
    a = s;
    if (!clubId.count(a))
    {
      clubName.push_back(a);
      clubId[a] = clubId.size();
    }
    personClubs.back().push_back(clubId[a]);
  }
  return true;
}

int main()
{
  int tests, tt = 0; scanf("%d\n\n", &tests);
  while (tests -- > 0)
  {
    if (tt ++) printf("\n");
    partyId.clear(), personId.clear(), clubId.clear();
    partyName.clear(), personName.clear(), clubName.clear();
    personParty.clear(), partyPeople.clear(), personClubs.clear();

    while (readPerson());

    sink = personId.size() + partyId.size() + clubId.size() + 1; vertices = sink + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    // Each party can elect at most clubSize / 2 - 1 people
    for (auto i: partyId)
      addEdge(source, 1 + i.second, (clubId.size() - 1) >> 1);
    // Each party has some people
    for (auto i: partyId)
      for (auto j: partyPeople[i.second])
        addEdge(1 + i.second, partyId.size() + 1 + j, 1);
    // Each club will elect a single person
    for (auto i: personId)
      for (int j: personClubs[i.second])
        addEdge(partyId.size() + 1 + i.second, partyId.size() + personId.size() + 1 + j, 1);
    // Sum all clubs
    for (auto i: clubId)
      addEdge(personId.size() + partyId.size() + 1 + i.second, sink, 1);

    int maxFlow = dinic();
    if (maxFlow < clubId.size())
      printf("Impossible.\n");
    else
    {
      int got[partyId.size()]; memset(got, 0, sizeof(got));
      for (auto i: clubId)
        for (Edge &e: graph[personId.size() + partyId.size() + 1 + i.second])
          if (e.flow && !e.capacity)
            printf("%s %s\n", personName[e.to - 1 - partyId.size()].c_str(), i.first.c_str());
    }
  }
  return(0);
}