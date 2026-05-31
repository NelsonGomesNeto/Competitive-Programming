#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
I missed that we must be able to iterate over the responses. So I tried to
minimize the number of times the answer was computed. But it ended up having the
same execution time of just iterating over the responses hahahaha.
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
  int n, l, r;
  std::string s;

  std::vector<int> memo_by_size;
  int CountSubstringsFromSize(const int sz) {
    int& res = memo_by_size[sz];
    if (res != -1) return res;
    if (sz == 0) return res = 0;
    const std::string t = s.substr(0, sz);
    return res = (int)kmp.AllOccurrences(s, t).size();
  }
  std::vector<int> ans;
  int BiggestSubstringWithAtLeastKOccurrences(const int k) {
    int& res = ans[k];
    if (res != -1) return res;
    int lo = 0, hi = n;
    while (lo < hi) {
      const int mid = (lo + hi + 1) >> 1;
      if (CountSubstringsFromSize(mid) >= k)
        lo = mid;
      else
        hi = mid - 1;
    }
    return res = lo;
  }

  KMP kmp;
  void Solve(const int lo, const int hi) {
    if (lo > hi) {
      return;
    }
    const int elo = BiggestSubstringWithAtLeastKOccurrences(lo),
              ehi = BiggestSubstringWithAtLeastKOccurrences(hi);
    const int mid = (lo + hi) >> 1;
    const int emid = BiggestSubstringWithAtLeastKOccurrences(mid);

    if (elo == emid) {
      for (int k = lo; k <= mid; ++k) ans[k] = elo;
    } else {
      Solve(lo + 1, mid - 1);
    }
    if (emid == ehi) {
      for (int k = mid; k <= hi; ++k) ans[k] = ehi;
    } else {
      Solve(mid + 1, hi - 1);
    }
  }

  bool Run() {
    if (!(std::cin >> n >> l >> r)) return false;
    std::cin >> s;
    kmp = KMP(s);

    memo_by_size.resize(n + 1, -1);
    ans.resize(n + 1, -1);
    Solve(l, r);
    for (int k = l; k <= r; ++k) {
      if (k != l) std::print(" ");
      std::print("{}", ans[k]);
    }
    std::println("");

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