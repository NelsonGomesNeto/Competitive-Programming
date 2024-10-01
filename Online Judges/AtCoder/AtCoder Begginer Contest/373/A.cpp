#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double

int main() {
  int ans = 0;
  for (int i = 0; i < 12; ++i) {
    std::string s;
    std::cin >> s;
    if (s.size() == i + 1) {
      ++ans;
    }
  }
  std::cout << ans << "\n";
  return 0;
}