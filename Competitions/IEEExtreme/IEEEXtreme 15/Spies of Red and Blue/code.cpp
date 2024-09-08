#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int na, nb, m;
vector<pair<char, int>> tree[2][maxN + 2];
pair<char, int> readNode()
{
  char kind; int num; scanf(" %c%d", &kind, &num);
  return make_pair(kind, num);
}

bool visited[2][maxN + 2];
pair<string, int> dfs(pair<char, int> u)
{
  for (int i = 0; i <= maxN + 1; i++) visited[0][i] = visited[1][i] = false;
  int depth = 0;
  while (u.second != 1)
  {
    if (tree[u.first == 'B'][u.second].empty()) return make_pair("0", 1e9);
    if (visited[u.first == 'B'][u.second]) return make_pair("0", 1e9);
    visited[u.first == 'B'][u.second] = true;
    u = tree[u.first == 'B'][u.second][0], depth++;
  }
  return make_pair(u.first == 'B' ? "BLUE" : "RED", depth);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &na, &nb, &m);

    for (int i = 0; i <= maxN + 1; i++) tree[0][i].clear(), tree[1][i].clear();
    for (int i = 1; i < na; i++)
    {
      auto u = readNode();
      auto v = make_pair(u.first, i + 1);
      tree[v.first == 'B'][v.second].push_back(u);
    }
    for (int i = 1; i < nb; i++)
    {
      auto u = readNode();
      auto v = make_pair(u.first, i + 1);
      tree[v.first == 'B'][v.second].push_back(u);
    }

    for (int i = 0; i < m; i++)
    {
      char op; scanf(" %c", &op);
      auto u = readNode(), v = readNode();
      if (op == 'w')
      {
        if (u.first == 'B') swap(u, v);

        auto da = dfs(u), db = dfs(v);
        map<string, int> res;
        res["BLUE"] = res["RED"] = 1e9;

        res[da.first] = min(res[da.first], da.second);
        res[db.first] = min(res[db.first], db.second);

        DEBUG {
          printf("\t%s %d\n", da.first.c_str(), da.second);
          printf("\t%s %d\n", db.first.c_str(), db.second);
          printf("%d %d\n", res["BLUE"], res["RED"]);
        }

        if (res["BLUE"] < res["RED"]) printf("BLUE %d\n", res["BLUE"]);
        else if (res["BLUE"] == res["RED"])
        {
          if (res["BLUE"] == 1e9) printf("NONE\n");
          else printf("TIE %d\n", res["BLUE"]);
        }
        else printf("RED %d\n", res["RED"]);
      }
      else
      {
        tree[u.first == 'B'][u.second].clear();
        tree[u.first == 'B'][u.second].push_back(v);
      }
    }
  }
  return 0;
}