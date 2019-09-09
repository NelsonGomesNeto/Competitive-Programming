#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble PI = acos(-1), PI2 = acos(-1) / 2.0;

struct Point
{
  ldouble x, y, angle, centerDist;
  char xStr[20], yStr[20];
  void read() { scanf("%[^,], %[^*\n]", xStr, yStr); x = atof(xStr), y = atof(yStr); }
  void print() { printf("%Lf, %Lf | %Lf | %Lf\n", x, y, angle, centerDist); }
  bool operator<(const Point &other) const { return angle > other.angle; }
  ldouble angleTo(Point &other) { return atan2(y - other.y, x - other.x); }
};
list<Point> pointsList;
vector<Point> points;
Point center = {0, 0};

int main()
{
  char sep;
  Point rightMost; rightMost.x = -1e9;
  while (scanf("%c", &sep) != EOF && sep == '*')
  {
    Point a; a.read();
    if (a.x > rightMost.x)
      rightMost = a, pointsList.push_front(a);
    else
      pointsList.push_back(a);
  }
  for (Point &a: pointsList)
    points.push_back(a);

  points[0].angle = PI;
  DEBUG points[0].print();
  for (int i = 1; i < points.size(); i ++)
  {
    points[i].angle = points[0].angleTo(points[i]);
    DEBUG points[i].print();
  }
  sort(points.begin() + 1, points.end());

  for (int i = 0; i < points.size(); i ++)
    printf("*%s, %s", points[i].xStr, points[i].yStr);
  printf("\n");
  
  DEBUG {
    printf("Execute[{");
    for (int i = 0; i < points.size(); i ++)
      printf("\"%c%d=(%Lf, %Lf)\"%c", 'A', i, points[i].x, points[i].y, i < points.size() - 1 ? ',' : ' ');
    printf("}]\n");
  }

  return(0);
}