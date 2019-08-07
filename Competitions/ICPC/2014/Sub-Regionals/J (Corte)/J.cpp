#include <bits/stdc++.h>
using namespace std;

struct Point
{
  double x, y;
};
const int maxN = 100; int n;
Point points[2*maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < 2*n; i ++)
    scanf("%lf %lf", &points[i].x, &points[i].y);

  

  return(0);
}