#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b, c;

__int128_t Cost(lli k, lli d) {
  __int128_t cost = (__int128_t)d * b;

  lli required_s = 0;
  const lli required_bun = 2 + (k - 1) - 2*d;
  if (required_bun > 0)
    required_s = max(required_s, (required_bun + 1) / 2);

  const lli required_cheese = k - 2*d;
  if (required_cheese > 0)
    required_s = max(required_s, required_cheese);

  cost += (__int128_t)required_s * a;

  return cost;
}
bool Can(lli k) {
  lli lo = 0, hi = k;
  while (hi - lo > 3) {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    __int128_t elo = Cost(k, midlo), ehi = Cost(k, midhi);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  __int128_t cost = numeric_limits<__int128_t>::max();
  for (lli i = lo; i <= hi; ++i) {
    cost = min(cost, Cost(k, i));
  }

  return cost <= c;
}
lli BinarySearch() {
  lli lo = 0, hi = 2*c;
  while (lo < hi) {
    lli mid = (lo + hi + 1) >> 1;
    if (Can(mid)) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%lld %lld %lld", &a, &b, &c);

    lli ans = BinarySearch();
    printf("Case #%d: %lld\n", test_case, ans);
  }
  return 0;
}
