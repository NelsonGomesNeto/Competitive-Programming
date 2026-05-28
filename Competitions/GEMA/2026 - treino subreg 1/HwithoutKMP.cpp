#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, ignore, k;
  std::string s;

  std::array<int, 26> cnt;

  std::array<int, 26> req;
  bool Can(const int sz) {
    const std::string t = s.substr(0, sz);
    std::ranges::fill(req, 0);
    for (const char c : t) ++req[c - 'a'];
    for (char c = 'a'; c <= 'z'; ++c) {
      if (req[c - 'a']*k > cnt[c - 'a']) return false;
    }

    int found = 1, pos = sz;
    while (found < k) {
      const std::size_t nxt_pos = s.find(t, pos);
      if (nxt_pos == s.npos) return false;
      pos = nxt_pos + sz;
      ++found;
    }
    return found >= k;
  }

  int Solve() {
    std::ranges::fill(cnt, 0);
    for (const char c : s) ++cnt[c - 'a'];

    int lo = 0, hi = n / k;
    while (lo < hi) {
      const int mid = (lo + hi + 1) >> 1;
      if (Can(mid)) lo = mid;
      else hi = mid - 1;
    }

    return lo;
  }

  bool Run() {
    if (!(std::cin >> n >> ignore >> k)) return false;
    std::cin >> s;

    const int ans = Solve();
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}