#include <bits/stdc++.h>
#define lli long long int

const lli kMod = 1e9 + 7;  // could be two as well

lli PowRec(lli x, lli y) {
  if (!y) return 1;
  lli ret = PowRec(x, y >> 1);
  ret = ret * ret % kMod;
  if (y & 1) ret = ret * x % kMod;
  return ret;
}

lli PowBottomUp(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1;
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
