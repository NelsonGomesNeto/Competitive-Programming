#include <bits/stdc++.h>
#define lli long long int

lli PowRec(lli x, lli y) {
  if (!y) return 1;
  lli ret = PowRec(x, y >> 1);
  ret *= ret;
  if (y & 1) ret *= x;
  return ret;
}

lli PowBottomUp(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1) ans *= x;
    x *= x, y >>= 1;
  }
  return ans;
}

lli Pow(lli x, lli y) {
  return PowBottomUp(x, y);
  // returnPowRec(x, y);
}

int main() {
  lli x, y;
  while (std::cin >> x >> y) {
    std::println("{}", Pow(x, y));
  }
  return 0;
}
