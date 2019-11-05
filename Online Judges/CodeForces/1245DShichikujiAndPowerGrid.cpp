#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;
const lli inf = LLONG_MAX;
struct City
{
  lli x, y, c, k; int connectedWith;
  void read() { scanf("%lld %lld", &x, &y); }
  bool operator<(const City &other) const { return c < other.c; }
};
bool alone[maxN], up[maxN];
City cities[maxN];
lli getCost(int i, int j)
{
  if (i == j)
    return cities[i].c;
  return (abs(cities[i].x - cities[j].x) + abs(cities[i].y - cities[j].y)) * (cities[i].k + cities[j].k);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    cities[i].read();
    cities[i].connectedWith = -1;
  }
  for (int i = 0; i < n; i ++)
    scanf("%lld", &cities[i].c);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &cities[i].k);

  lli totalCost = 0;
  vector<int> powerPlant;
  vector<pair<int, int>> connections;
  for (int i = 0; i < n; i ++)
  {
    int best = -1;
    for (int j = 0; j < n; j ++)
      if (cities[j].c != inf && (best == -1 || cities[j].c < cities[best].c))
        best = j;

    totalCost += cities[best].c;
    cities[best].c = inf;
    if (cities[best].connectedWith == -1)
      powerPlant.push_back(best);
    else
      connections.push_back({best, cities[best].connectedWith});

    for (int j = 0; j < n; j ++)
      if (cities[j].c != inf && getCost(best, j) < cities[j].c)
        cities[j].c = getCost(best, j), cities[j].connectedWith = best;
  }

  printf("%lld\n", totalCost);
  printf("%d\n", (int) powerPlant.size());
  for (int i = 0; i < powerPlant.size(); i ++)
    printf("%d%c", powerPlant[i] + 1, i < powerPlant.size() - 1 ? ' ' : '\n');
  printf("%d\n", (int) connections.size());
  for (auto &p: connections)
    printf("%d %d\n", p.first + 1, p.second + 1);

  return 0;
}
