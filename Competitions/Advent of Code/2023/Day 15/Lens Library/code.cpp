#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::vector<std::string> sequences;

int Hash(const std::string& s) {
  int ans = 0;
  for (int c : s) {
    ans += c;
    ans *= 17;
    ans %= 256;
  }
  return ans;
}

int main() {
  for (std::string s; std::getline(std::cin, s, ',');) {
    sequences.push_back(s);
  }

  int ans = 0;
  for (const auto& s : sequences) {
    ans += Hash(s);
  }
  std::cout << ans << std::endl;
  return 0;
}
