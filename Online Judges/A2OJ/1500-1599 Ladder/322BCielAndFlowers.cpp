#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  lli r, g, b; scanf("%lld %lld %lld", &r, &g, &b);
  lli smallest = max(min(r, min(g, b)) - 1, 0LL);
  lli ans = smallest; r -= smallest; g -= smallest; b -= smallest;
  ans += r / 3 + g / 3 + b / 3; r %= 3; g %= 3; b %= 3;
  ans += min(r, min(g, b));
  printf("%lld\n", ans);
  return(0);
}
