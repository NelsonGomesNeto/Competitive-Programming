#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
It's possible to simply binary search the answer and check by literally
searching for all the occurrences.
It's even possible to do it without KMP if you do some O(1) checks like "are
there enough occurrences of each letter?". ~1.5s
IIUC it's O(lg(n)*n^2) but the optimization make it almost impossible to break.

With KMP it's O(lg(n)*n) and runs in 46ms hahaha.

This was a great opportunity for me to improve my KMP \o/.
*/

struct KMP {
  std::vector<int> pi;
  KMP() {}
  KMP(const std::string& s) {
    pi.resize(s.size() + 1);
    pi[0] = -1;
    for (int i = 0, j = -1; i < s.size();) {
      while (j >= 0 && s[i] != s[j]) j = pi[j];
      pi[++i] = ++j;
    }
  }
  // Returns all occurrences of `sub` on `s`.
  std::vector<int> AllOccurrences(const std::string& s,
                                  const std::string& sub) const {
    std::vector<int> occurrences;
    for (int i = 0, j = 0; i < s.size();) {
      while (j >= 0 && s[i] != sub[j]) j = pi[j];
      i++, j++;
      if (j == sub.size()) {
        occurrences.push_back(i - j);
        // j = pi[j];
        // Ignore occurrences which overlap.
        j = 0;
      }
    }
    return occurrences;
  }
};

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
      if (req[c - 'a'] * k > cnt[c - 'a']) return false;
    }

    return (int)kmp.AllOccurrences(s, t).size() >= k;
  }

  KMP kmp;
  int Solve() {
    std::ranges::fill(cnt, 0);
    for (const char c : s) ++cnt[c - 'a'];

    kmp = KMP(s);

    int lo = 0, hi = n / k;
    while (lo < hi) {
      const int mid = (lo + hi + 1) >> 1;
      if (Can(mid))
        lo = mid;
      else
        hi = mid - 1;
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
