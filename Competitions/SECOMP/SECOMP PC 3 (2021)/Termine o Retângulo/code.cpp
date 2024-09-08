#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
};
Point points[3];

int main()
{
  for (int i = 0; i < 3; i++)
    points[i].read();

  map<int, int> xcnt, ycnt;
  for (int i = 0; i < 3; i++) xcnt[points[i].x]++, ycnt[points[i].y]++;

  for (auto &x: xcnt)
    if (x.second == 1)
      printf("%d ", x.first);
  for (auto &y: ycnt)
    if (y.second == 1)
      printf("%d\n", y.first);

  return 0;
}