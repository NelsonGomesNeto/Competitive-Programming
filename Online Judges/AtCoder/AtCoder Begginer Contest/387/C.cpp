#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxDigits = 19, kMaxAlpha = 9;
const int kNilDigit = kMaxAlpha + 1;

struct TestCase {
  lli l, r;

  std::vector<int> GetDigits(lli x) {
    std::vector<int> digits;
    if (x == 0) digits.push_back(0);
    while (x) {
      digits.push_back(x % 10);
      x /= 10;
    }
    std::ranges::reverse(digits);
    return digits;
  }
  std::vector<std::vector<std::vector<std::vector<lli>>>> memo;
  lli f(const std::vector<int>& digits, const int i = 0,
        const int biggest = kNilDigit, const int start_digit = 0,
        const bool equal = true) {
    if (i == digits.size()) {
      // std::cout << std::format("\t{} {} {} {} | {}\n", i, biggest,
      // start_digit,
      //                          equal, deb);
      return biggest != kNilDigit;
    }
    lli& ans = memo[i][biggest][start_digit][equal];
    if (ans != -1) return ans;

    ans = 0;
    for (int d = 0, end = biggest == kNilDigit
                              ? (i == 0 ? digits[0] : (equal ? digits[i] : 9))
                              : (equal ? std::min(biggest - 1, digits[i])
                                       : biggest - 1);
         d <= end; ++d) {
      const int nxt_biggest = biggest == kNilDigit && d != 0 ? d : biggest;
      ans +=
          f(digits, i + 1, nxt_biggest,
            biggest == kNilDigit && nxt_biggest != kNilDigit ? i : start_digit,
            equal && (d == digits[i]));
    }
    return ans;
  }
  lli f(lli x) {
    memo.clear();
    memo.resize(
        kMaxDigits,
        std::vector<std::vector<std::vector<lli>>>(
            kMaxAlpha + 2, std::vector<std::vector<lli>>(
                               kMaxDigits, std::vector<lli>(2, -1))));
    const std::vector<int> digits = GetDigits(x);
    lli res = f(digits);
    // DEBUG std::cout << std::format("\t{}: {}\n", x, res);
    return res;
  }

  bool Run() {
    if (!(std::cin >> l >> r)) return false;
    lli ans = f(r) - f(l - 1);
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
