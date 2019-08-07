#include <bits/stdc++.h>
#define lli long long int
using namespace std;

// Plane: Ax + By + Cz = D
const int maxM = 500, maxN = 1e4, inf = 1e9; int m, n;
int planes[maxM][4], planets[maxN][3];
vector<set<int>> regions;
int planetsRegion[maxN]; double distToRegion[maxN];

double distToPlane(int plane, int planet)
{
  double a = planes[plane][0], b = planes[plane][1], c = planes[plane][2], d = -planes[plane][3]; // REMEMBER THAT'S *MINUS* D
  double x = planets[planet][0], y = planets[planet][1], z = planets[planet][2];
  return((a*x + b*y + c*z + d) / sqrt(a*a + b*b + c*c));
}

int main()
{
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i ++) scanf("%d %d %d %d", &planes[i][0], &planes[i][1], &planes[i][2], &planes[i][3]);
  for (int i = 0; i < n; i ++) scanf("%d %d %d", &planets[i][0], &planets[i][1], &planets[i][2]);

  map<vector<lli>, int> regions;
  for (int i = 0; i < n; i ++)
  {
    vector<lli> r; r.push_back(0);
    for (int j = 0; j < m; j ++)
    {
      double d = distToPlane(j, i);
      if (j % 64 == 0) r.push_back(0);
      r[r.size() - 1] |= ((lli) (d > 0)) << (j % 64);
    }
    if (!regions.count(r)) regions[r] = 0;
    regions[r] ++;
  }
  int best = 0;
  for (auto i: regions) best = max(best, i.second);
  printf("%d\n", best);

  return(0);
}