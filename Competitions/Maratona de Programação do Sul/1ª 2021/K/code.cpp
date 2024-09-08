#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 15; int n, c, t;
char s[11];
string readString()
{
  scanf(" %s", s);
  return string(s);
}
map<string, vector<string>> graph;

set<string> findParents(string origin)
{
  set<string> parents;
  queue<string> q; q.push(origin);
  while (!q.empty())
  {
    string u = q.front(); q.pop();
    parents.insert(u);
    for (string v: graph[u])
      q.push(v);
  }
  return parents;
}

int main()
{
  while (~scanf("%d %d %d", &n, &c, &t))
  {
    for (int i = 0; i < c; i++)
    {
      string u = readString(), v = readString(), w = readString();
      graph[w].push_back(u);
      graph[w].push_back(v);
    }

    for (int i = 0; i < t; i++)
    {
      string u = readString(), v = readString();
      set<string> up = findParents(u);
      set<string> vp = findParents(v);
      bool has = false;
      for (string p: up)
        if (vp.count(p))
        {
          has = true;
          break;
        }
      printf("%s\n", has ? "verdadeiro" : "falso");
    }
  }
  return 0;
}