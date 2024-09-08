#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
};
Point points[maxN];

int solve(int i = 0, int prv = -1)
{

}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
