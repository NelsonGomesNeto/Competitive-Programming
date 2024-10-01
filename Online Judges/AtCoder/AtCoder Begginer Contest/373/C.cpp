#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int main() {
  int n;
  while (std::cin >> n) {
    std::vector<int> a, b;
    a.resize(n), b.resize(n);
    for (int& aa : a) std::cin >> aa;
    for (int& bb : b) std::cin >> bb;

    const int ans = *std::max_element(a.begin(), a.end()) +
                    *std::max_element(b.begin(), b.end());
    std::cout << ans << "\n";
  }
  return 0;
}