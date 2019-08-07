#include <stdio.h>
#include <vector>
#include <limits.h>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define inf INT_MAX
#define lli long long int
int DEBUG = 0;

lli min(lli a, lli b)
{
  return(a > b ? b : a);
}

void dijkstra(vector<vector<lli> > graph, lli cost[], lli visited[], lli path[], lli manaNeeded[])
{
  cost[1] = manaNeeded[1];
  path[1] = 1;
  priority_queue<pair<lli, lli>, vector<pair<lli, lli> >, greater<pair<lli, lli> > > queue;
  queue.push( {cost[1], 1} );

  while (!queue.empty())
  {
    lli v = queue.top().second; queue.pop();

    if (visited[v] == 1) continue;
    visited[v] = 1;

    if (DEBUG == 1) printf("At node: %lld\n", v);
    for (auto u : graph[v])
    {
      if (DEBUG == 1) printf("\tExpanding: %lld | %lld %lld %lld\n", u, cost[v], manaNeeded[u], cost[u]);
      if (cost[v] + manaNeeded[u] < cost[u])
      {
        cost[u] = cost[v] + manaNeeded[u];
        path[u] = v;
        queue.push( {cost[u], u} );
      }
    }
  }
}

int main()
{
  lli magics, saloons, galeries, monsters;
  while (scanf("%lld %lld %lld %lld", &magics, &saloons, &galeries, &monsters)
      && !(magics == 0 && saloons == 0 && galeries == 0 && monsters == 0))
  {
    vector<pair<lli, lli> > magic; lli mana, damage;
    for (lli i = 0; i < magics; i ++)
    {
      scanf("%lld %lld", &mana, &damage);
      magic.pb(mp(mana, damage));
    }

    vector<vector<lli> > graph; lli a, b;
    graph.resize(saloons + 1);
    for (lli i = 0; i < galeries; i ++)
    {
      scanf("%lld %lld", &a, &b);
      graph[a].pb(b); graph[b].pb(a);
    }

    lli dp[1001];
    for (int i = 0; i <= 1000; i ++)
      dp[i] = inf;
    dp[0] = 0;
    for (int hp = 0; hp <= 1000; hp ++) // Killing everysingle monster :)
    {
      for (int i = 0; i < magics; i ++)
      {
        if (hp >= magic[i].second)
          dp[hp] = min(dp[hp], dp[hp - magic[i].second] + magic[i].first);
        else
          dp[hp] = min(dp[hp], magic[i].first);
      }
    }
    if (DEBUG == 1)
    {
      for (int i = 0; i < 999; i ++)
      {
        if (i < 60)
          printf("%lld ", dp[i]);
      } printf("\n");
    }

    lli neededMana[saloons + 1]; lli place, hp;
    for (lli i = 0; i <= saloons; i ++)
      neededMana[i] = 0;
    for (lli i = 0; i < monsters; i ++)
    {
      scanf("%lld %lld", &place, &hp);
      neededMana[place] += dp[hp];
      if (DEBUG == 1) printf("%lld %lld %lld %lld\n", place, hp, dp[hp], neededMana[place]);
    }

    if (DEBUG == 1)
    {
      for (auto m : magic)
        printf("%lld %lld\n", m.first, m.second);
      lli k = 0;
      for (auto v : graph)
      {
        printf("%lld -> ", k);
        for (auto u : v)
        {
          printf("%lld ", u);
        }
        k ++;
        printf("\n");
      } printf("\n");
      for (auto m : neededMana)
        if (m != 0)
          printf("%lld\n", m);
      printf("\n");
    }

    lli cost[saloons + 1], visited[saloons + 1], path[saloons + 1];
    for (lli i = 0; i <= saloons; i ++)
    {
      cost[i] = inf;
      visited[i] = 0;
      path[i] = -1;
    }
    dijkstra(graph, cost, visited, path, neededMana);
    if (DEBUG == 1)
    {
      printf("Cost: ");
      for (auto c : cost)
        printf("%lld ", c);
      printf("\n");
      printf("Mana: ");
      for (auto m : neededMana)
        printf("%lld ", m);
      printf("\n");
      printf("Path: ");
      for (auto p : path)
        printf("%lld ", p);
      printf("\n");
    }

    printf("%lld\n", cost[saloons] == inf ? -1 : cost[saloons]);
  }

  return(0);
}
/*
DP explanation:
if (hp >= magic[i].second)
  I don't know how to kill it with that amount of hp, but:
  It is calculated above on else, so: I get the amount of mana needed to kill with
  hp - magic[i].second (damage) and then finally kill it with this magic :)
  dp[hp] = min(dp[hp], dp[hp - magic[i].second] + magic[i].first);
else
  dp[hp] = min(dp[hp], magic[i].first);

Example:
hp = 5, damage = 3
else have calculated dp[2]
I don't know how to kill it with 5, but I know with 5 - 3, so:
mana needed to kill that hp(5) monster will be: previous + mana of this magic
*/
