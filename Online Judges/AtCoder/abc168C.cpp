#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double pi = acos(-1);

struct Point
{
  double x, y;
  void print()
  {
    printf("(%.3lf, %.3lf)\n", x, y);
  }
  double dist(Point &other)
  {
    return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
};

int main()
{
  int a, b, h, m;
  while (scanf("%d %d %d %d", &a, &b, &h, &m) != EOF)
  {
    double minuteAngle = (double)m / 60 * 2 * pi;
    double hourAngle = (double)h / 12 * 2 * pi + minuteAngle / 12;
    Point hour = {a * cos(hourAngle), a * sin(hourAngle)};
    DEBUG hour.print();
    Point minute = {b * cos(minuteAngle), b * sin(minuteAngle)};
    DEBUG minute.print();
    printf("%.15lf\n", hour.dist(minute));
  }
  return 0;
}