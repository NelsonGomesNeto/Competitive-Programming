#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::string s, t;
  std::vector<std::pair<int, int>> lrs;
  std::vector<int> in, out;

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    std::cin >> s;
    std::cin >> t;
    lrs.resize(m);
    for (auto& [l, r] : lrs) {
      std::cin >> l >> r;
      --l, --r;
    }

    in.resize(n, 0), out.resize(n, 0);
    for (const auto [l, r] : lrs) {
      ++in[l], ++out[r];
    }
    std::string ans;
    ans.reserve(n);
    for (int i = 0, curr = 0; i < n; ++i) {
      curr += in[i];
      ans.push_back((curr & 1) ? t[i] : s[i]);
      curr -= out[i];
    }
    std::cout << ans << "\n";

    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}