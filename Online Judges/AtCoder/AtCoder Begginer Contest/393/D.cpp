#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::string s;
  std::vector<lli> l, r;
  std::vector<bool> hasl, hasr;
  bool Run() {
    if (!(std::cin >> n)) return false;
    std::cin >> s;

    l.resize(n), r.resize(n);
    hasl.resize(n), hasr.resize(n);

    auto Fill = [&](std::vector<lli>& side, std::vector<bool>& has,
                    const int lo, const int hi, const int delta) {
      lli cnt = 0, sum = 0;
      for (int i = lo; i != hi; i += delta) {
        if (s[i] == '1') {
          ++cnt;
        } else {
          sum += cnt;
        }
        side[i] = sum;
        has[i] = cnt > 0;

        DEBUG std::cout << "\t\t" << i << " " << side[i] << "\n";
      }
    };
    Fill(l, hasl, 0, n, 1);
    Fill(r, hasr, n - 1, -1, -1);

    lli ans = std::numeric_limits<lli>::max();
    for (int i = 0; i < n; ++i) {
      lli a = std::numeric_limits<lli>::max(),
          b = std::numeric_limits<lli>::max();
      if (i + 1 < n) {
        if (s[i] == '1')
          a = l[i] + r[i];
        else
          a = l[i] + r[i + hasl[i]];
        DEBUG2 std::cout << "\t\t" << hasl[i] << " | " << l[i] << " "
                         << r[i + hasl[i]] << "\n";
      }
      if (i) {
        if (s[i] == '1')
          b = l[i] + r[i];
        else
          b = l[i - hasr[i]] + r[i];
        DEBUG2 std::cout << "\t\t" << hasr[i] << " | " << l[i - hasr[i]] << " "
                         << r[i] << "\n";
      }

      DEBUG2 std::cout << "\t" << i << " " << a << " " << b << "\n";
      ans = std::min(ans, l[i] + r[i]);
    }
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
