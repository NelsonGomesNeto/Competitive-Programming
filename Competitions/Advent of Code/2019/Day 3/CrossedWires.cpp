#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int di[256], dj[256];
map<pair<int, int>, int> positions[2];

void read(int kind)
{
  char dir; int dist; char end = '0';
  int i = 0, j = 0, steps = 0;
  while (scanf("%c%d%c", &dir, &dist, &end) != EOF && end == ',')
  {
    while (dist --)
    {
      i += di[dir], j += dj[dir];
      positions[kind][{i, j}] = ++ steps;
    }
  }
}

int manhattan(int i, int j)
{
  return abs(i) + abs(j);
}

int main()
{
  di['R'] = di['L'] = 0, dj['R'] = 1, dj['L'] = -1;
  di['U'] = 1, di['D'] = -1, dj['U'] = dj['D'] = 0;

  read(0);
  read(1);

  // int ci = 10000, cj = 10000;
  // for (auto &p: positions[0])
  //   if (positions[1].count(p) && manhattan(p.first, p.second) < manhattan(ci, cj))
  //     ci = p.first, cj = p.second;
  // printf("%d\n", manhattan(ci, cj));
  int ci = 10000, cj = 10000, steps = 1e9;
  for (auto &p: positions[0])
    if (positions[1].count(p.first) && p.second + positions[1][p.first] < steps)
      steps = p.second + positions[1][p.first];
  printf("%d\n", steps);

  return 0;
}