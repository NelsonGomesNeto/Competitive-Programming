#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* The area of a polygon can be calculated using the shoelace formula:
  Area = 1 / 2 * (p[i] ^ p[(i + 1) % n])
  Where the ^ operator stands for:
    a.x * b.y - b.x * a.y

  So, if the area is divisible by two: it's an integer area

  The problem is: that formula will only work if we use the vertices of
  the convex hull...

  We can build the convex hull online
*/

const int maxN = 80; int n;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  void print() { printf("%d %d\n", x, y); }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  // bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
  int crossProduct(const Point &other) const { return x*other.y - y*other.x; }
  bool operator<(const Point &other) const { return crossProduct(other) < 0; }
  // bool operator<(const Point &other) const { return atan2(y, x) >= atan2(other.y, other.x); }
  int signedArea(const Point &b, const Point &c) { return x*(b.y - c.y) + b.x*(c.y - y) + c.x*(y - b.y); }
  bool clockwise(const Point &b, const Point &c) { return signedArea(b, c) < 0; }
  bool counterClockwise(const Point &b, const Point &c) { return signedArea(b, c) > 0; }
};
vector<Point> points;

/*
  0, 0
  1, 2
  1, 0

  1, 2
  0, 1
  1, 0
*/
const lli mod = 1e9 + 7;
bool areaDivisibleByTwo(deque<Point> curr)
{
  if (curr.size() < 3) return false;
  DEBUG printf("Testing (%d)\n", (int)curr.size());
  DEBUG for (Point &p: curr) p.print();
  int area = curr.back().crossProduct(curr[0]);
  for (int i = 1; i < curr.size(); i++)
    area += curr[i - 1].crossProduct(curr[i]);
  area = abs(area);
  DEBUG printf("--- %d\n", area);
  return !(area & 1LL);
}
lli solve(int i = 0, deque<Point> curr = {})
{
  if (i == n) return areaDivisibleByTwo(curr);

  lli ans = solve(i + 1, curr);
  while (curr.size() >= 2 && curr[curr.size() - 2].counterClockwise(curr.back(), points[i]))
    curr.pop_back();
  curr.push_back(points[i]);
  ans = (ans + solve(i + 1, curr)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    points.clear(); points.resize(n);
    for (int i = 0; i < n; i++)
      points[i].read();

    vector<Point> aux = points;
    sort(points.begin(), points.end());

    lli ans = solve();
    // for (int i = 0; i < n; i++)
    // {
    //   for (int j = 0; j < n; j++)
    //     points[j] = aux[i] - aux[j];
    //   sort(points.begin(), points.end());
    //   ans = (ans + solve(1, {points[0]})) % mod;
    // }
    printf("%lld\n", ans);
  }
  return 0;
}