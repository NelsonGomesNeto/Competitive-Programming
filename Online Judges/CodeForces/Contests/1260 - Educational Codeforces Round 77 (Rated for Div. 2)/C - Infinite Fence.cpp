#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli r, b, k; scanf("%lld %lld %lld", &r, &b, &k);
    if (r > b) swap(r, b);
    int spacing = (b - 1) / r;
    printf("%s\n", spacing >= k ? "REBEL" : "OBEY");
  }
  return 0;
}
