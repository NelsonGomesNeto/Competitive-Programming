#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;
const long double pi = acos(-1);
int s[maxN], arr[maxN];

struct Point
{
  long double x, y;
  void print() { printf("%Lf %Lf\n", x, y); }
};

long double degToRad(long double angle)
{
  return(angle * pi / 180.0);
}

long double triangleArea(Point a, Point b, Point c)
{
  // triangle area given points a, b and c
  // 1/2 * det({a.x, b.x, c.x},
  //           {a.y, b.y, c.y},
  //           {  1,   1,   1})
  // */
  return(-((a.x * b.y * 1 + b.x * c.y * 1 + c.x * a.y * 1) - (b.x * a.y * 1 + a.x * c.y * 1 + c.x * b.y * 1)) / 2.0);
}

long double area()
{
  long double angle = degToRad(360 / 2.0 / n), area = 0;
  long double co = cos(angle), si = sin(angle);
  Point a = {0, 0}, b, c;
  for (int i = 0; i < n; i ++)
  {
    b = {arr[i] * co, arr[i] * si};
    c = {arr[(i + 1) % n] * co, -arr[(i + 1) % n] * si};
    area += triangleArea(a, b, c);
  }
  return(area);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &s[i]);
  sort(s, s+n);
  deque<int> d;
  for (int i = 0; i < n; i ++)
    if (i & 1) d.push_back(s[i]);
    else d.push_front(s[i]);
  for (int i = 0; !d.empty(); i ++, d.pop_front()) arr[i] = d.front();

  // for (int i = 0; i < n; i ++) printf("%d%c", arr[i], i < n - 1 ? ' ' : '\n');

  long double ans = area();
  printf("%.3Lf\n", ans);


  return(0);
}