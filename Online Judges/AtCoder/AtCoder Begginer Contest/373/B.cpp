#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double

int main() {
  std::string s;
  while (std::cin >> s) {
    std::map<char, int> pos;
    for (int i = 0; i < s.size(); ++i) {
      pos[s[i]] = i;
    }

    int curr = pos['A'];
    int ans = 0;
    for (char c = 'A'; c <= 'Z'; ++c) {
      const int p = pos[c];
      ans += std::abs(p - curr);
      curr = p;
    }
    std::cout << ans << "\n";
  }
  return 0;
}