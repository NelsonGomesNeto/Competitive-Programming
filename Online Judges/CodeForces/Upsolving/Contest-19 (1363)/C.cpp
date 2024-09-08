#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

string players[2] = {"Ayush", "Ashish"};


int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  while (t--)
  {
    int n, x; scanf("%d %d", &n, &x); x--;
    vector<int> tree[n];
    int indegree[n]; memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < n - 1; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
      indegree[u]++, indegree[v]++;
    }

    set<int> leafs;
    int winner = -1;
    for (int i = 0; i < n; i++)
      if (indegree[i] <= 1)
      {
        leafs.insert(i);
        if (i == x) winner = 0;
      }

    int turn = 0;
    while (winner == -1)
    {
      int toRemove = -1;
      list<int> toAdd;

      for (int i: leafs)
      {
        bool ignore = false;
        for (int v: tree[i])
          if (v == x && indegree[v] - 1 == 1)
            ignore = true;
        if (!ignore)
        {
          toRemove = i;
          for (int v: tree[i])
            if (--indegree[v] == 1)
              toAdd.push_back(v);
          break;
        }
      }

      if (toRemove != -1)
      {
        leafs.erase(toRemove);
        for (int i: toAdd) leafs.insert(i);
      }
      else winner = !turn;
      turn = !turn;
    }
    printf("%s\n", players[winner].c_str());
  }
  return 0;
}
