#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Through a bruteforce, I found that chosing is not important.
So, S will be beautiful as long as the xnor of all elements is 1! \o/

Through another brute force, I found that the number of 1s don't matter
So, S will be beautiful as long as cnt(0) is even! \o/

011011100101110111100010011010
*/

struct TestCase {
  int n;
  std::string s;
  std::vector<std::vector<lli>> right_sum;
  std::vector<int> zero_pos;
  bool Run() {
    if (!(std::cin >> n)) return false;
    std::cin >> s;

    for (int i = 0; i < n; ++i) {
      if (s[i] != '0') continue;
      zero_pos.push_back(i);
    }

    right_sum.resize(2, std::vector<lli>(n, 0));
    std::vector<int> cnt(2, 0);
    for (int i = s.size() - 1, parity = false; i >= 0; --i) {
      ++cnt[parity];
      right_sum[parity][i] = cnt[parity];
      parity ^= s[i] == '0';
    }

    lli including_zero_pairs = 0;
    for (int i = 1, parity = false; i < (int)zero_pos.size();
         ++i, parity = !parity) {
      int pos = zero_pos[i];
      int left_alternatives = zero_pos[i - 1] + 1;
      if (i > 1) left_alternatives = zero_pos[i - 1] - zero_pos[i - 2];
      // DEBUG std::println("\t{} | {} | {} {}", pos, left_alternatives,
      //                    right_sum[false][pos], right_sum[true][pos]);
      including_zero_pairs += (lli)left_alternatives *
                              (right_sum[false][pos] + right_sum[true][pos]);
    }
    DEBUG {
      lli corr_including_zeros = 0;
      for (int lo = 0; lo < n; ++lo) {
        for (int hi = lo + 1; hi < n; ++hi) {
          int zeroes = 0;
          for (int i = lo; i <= hi; ++i) {
            zeroes += s[i] == '0';
          }
          if (zeroes < 2 || (zeroes & 1)) continue;
          // DEBUG if (n <= 7)
          //     std::println("\t\t{} {} | {}", lo, hi, s.substr(lo, hi - lo + 1));
          ++corr_including_zeros;
        }
      }
      // DEBUG std::println("\t{} {}", including_zero_pairs, corr_including_zeros);
    }

    lli only_ones = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] != '1') continue;
      int j = i;
      while (j + 1 < n && s[j + 1] == '1') ++j;
      int sz = j - i + 1;
      only_ones += ((lli)sz * (sz + 1)) >> 1;
      i = j;
    }

    lli ans = including_zero_pairs + only_ones;

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
