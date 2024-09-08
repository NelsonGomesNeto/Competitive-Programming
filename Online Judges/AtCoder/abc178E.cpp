#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); x--, y--; }
  lli dist(Point &other)
  {
    return abs(x - other.x) + abs(y - other.y);
  }
};
Point points[maxN];

vector<Point> getClosests(Point from)
{
  vector<pair<lli, int>> dists(n);
  for (int i = 0; i < n; i++)
    dists[i] = {points[i].dist(from), i};
  sort(dists.begin(), dists.end());
  vector<Point> ans(n);
  for (int i = 0; i < n; i++)
    ans[i] = points[dists[i].second];
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    vector<vector<Point>> closests;
    closests.push_back(getClosests(Point{0, 0}));
    closests.push_back(getClosests(Point{0, (lli)1e9}));
    closests.push_back(getClosests(Point{(lli)1e9, (lli)1e9}));
    closests.push_back(getClosests(Point{(lli)1e9, 0}));
    // vector<Point> leftdown = getClosests(Point{0, 0});
    // vector<Point> leftup = getClosests(Point{0, (lli)1e9});
    // vector<Point> rightup = getClosests(Point{(lli)1e9, (lli)1e9});
    // vector<Point> rightdown = getClosests(Point{(lli)1e9, 0});

    lli ans = 0;
    for (int i = 0; i < 4; i++)
      for (int j = i + 1; j < 4; j++)
        ans = max(ans, closests[i][0].dist(closests[j][0]));
    printf("%lld\n", ans);
  }
  return 0;
}