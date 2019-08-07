#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100*15; int n, m;
vector<vector<string>> semesters;
map<string, vector<string>> graph;
map<string, int> indegree, priority;

int main()
{
  while (scanf("%d %d", &n, &m) != EOF && !(!n && !m))
  {
    graph.clear(), indegree.clear(), semesters.clear(), priority.clear();

    for (int i = 0; i < n; i ++)
    {
      string u; int k; cin >> u >> k;
      if (!indegree.count(u)) indegree[u] = 0;
      if (!priority.count(u)) priority[u] = priority.size();
      for (int j = 0; j < k; j ++)
      {
        string v; cin >> v;
        graph[v].push_back(u);
        if (!indegree.count(v)) indegree[v] = 0;
        if (!priority.count(v)) priority[v] = priority.size();
        indegree[u] ++;
      }
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    for (auto &u: priority)
      if (indegree[u.first] == 0)
        pq.push({u.second, u.first});
    while (!pq.empty())
    {
      semesters.push_back(vector<string>());
      for (int i = 0; i < m && !pq.empty(); i ++)
      {
        string u = pq.top().second; pq.pop();
        semesters.back().push_back(u);
      }
      for (int i = 0; i < semesters.back().size(); i ++)
        for (string &v: graph[semesters.back()[i]])
          if ((-- indegree[v]) == 0)
            pq.push({priority[v], v});
    }

    printf("Formatura em %d semestres\n", (int) semesters.size());
    for (int i = 0; i < semesters.size(); i ++)
    {
      sort(semesters[i].begin(), semesters[i].end());
      printf("Semestre %d :", i + 1);
      for (int j = 0; j < semesters[i].size(); j ++)
        printf(" %s", semesters[i][j].c_str());
      printf("\n");
    }
  }
  return(0);
}