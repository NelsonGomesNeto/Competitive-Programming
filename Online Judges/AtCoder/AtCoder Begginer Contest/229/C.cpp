#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n; lli w;
struct Cheese
{
  lli a; int b;
  void read() { scanf("%lld %d", &a, &b); }
  bool operator<(const Cheese &other) const { return a > other.a; }
};
Cheese cheeses[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &w))
  {
    for (int i = 0; i < n; i++)
      cheeses[i].read();
    sort(cheeses, cheeses+n);

    lli ans = 0, currW = 0;
    for (int i = 0; i < n; i++)
    {
      lli toAdd = min((lli)cheeses[i].b, w - currW);
      ans += toAdd * cheeses[i].a;
      currW += toAdd;
    }
    printf("%lld\n", ans);
  }
  return 0;
}