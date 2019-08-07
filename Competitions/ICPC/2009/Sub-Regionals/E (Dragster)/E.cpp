#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
double prob[301][301];
int n, tree[602][2];
int nextRace[602];
vector<pair<int, double> > race[602];

void go(int u)
{
  if (u <= n) return;

  if (tree[u][0] <= n && tree[u][1] <= n)
  {
    race[u].push_back({tree[u][0], prob[tree[u][0]][tree[u][1]]});
    race[u].push_back({tree[u][1], prob[tree[u][1]][tree[u][0]]});
    return;
  }

  go(tree[u][0]);
  go(tree[u][1]);

  if (tree[u][0] <= n || tree[u][1] <= n)
  {
    double win = 0;
    int competidor = tree[u][0] <= n ? tree[u][0] : tree[u][1];
    int raceToDiscover = tree[u][0] <= n ? tree[u][1] : tree[u][0];
    for (auto v: race[raceToDiscover])
    {
      win += prob[competidor][v.first] * v.second;
      race[u].push_back({v.first, prob[v.first][competidor] * v.second});
    }
    race[u].push_back({competidor, win});
    return;
  }

  for (auto v: race[tree[u][0]])
  {
    double win = 0;
    for (auto w: race[tree[u][1]])
      win += prob[v.first][w.first] * w.second * v.second;
    race[u].push_back({v.first, win});
  }
  for (auto w: race[tree[u][1]])
  {
    double win = 0;
    for (auto v: race[tree[u][0]])
      win += prob[w.first][v.first] * v.second * w.second;
    race[u].push_back({w.first, win});
  }
  return;
}

int main()
{
  while (scanf("%d", &n) != EOF && n)
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%lf", &prob[i + 1][j + 1]);

    memset(nextRace, -1, sizeof(nextRace));
    for (int i = n + 1; i < 2*n; i ++)
    {
      scanf("%d %d", &tree[i][0], &tree[i][1]);
      nextRace[tree[i][0]] = nextRace[tree[i][1]] = i;
      race[i].clear();
    }

    int root = 1, at = 1;
    while (at != -1)
    {
      root = at;
      at = nextRace[at];
    }
    go(root);
    DEBUG for (int i = n + 1; i < 2*n; i ++)
    {
      printf("%d", i);
      for (auto j: race[i])
        printf(" (%d %.2lf)", j.first, j.second);
      printf("\n");
    }

    for (auto winner: race[root])
      if (winner.first == 1)
      {
        printf("%.6lf\n", winner.second); break;
      }
  }
  return(0);
}
