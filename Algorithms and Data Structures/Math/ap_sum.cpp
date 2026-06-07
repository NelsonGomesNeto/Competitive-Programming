#include <bits/stdc++.h>
#define lli long long int

lli ApSum(lli a1, lli n, lli d) {
  lli an = a1 + (n - 1) * d;
  return n * (a1 + an) >> 1LL;
}

// an = a1 + (n - 1)*q)
// lli apSum(lli a1, lli an, lli n) { return (n * (a1 + an) / 2.0); }

// lli apSum(lli a1, lli n, lli q)
// {
//   return (a1+a1+(n-1)*q)*n / 2LL;
// }

int main() {
  lli a1, n, d;
  while (std::cin >> a1 >> n >> d) {
    std::println("ApSum(a1={}, n={}, d={}) = {}", a1, n, d, ApSum(a1, n, d));
  }
  return (0);
}