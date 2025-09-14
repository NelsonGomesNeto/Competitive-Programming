#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// 222, 221, 212, 211
// 6226, 6216, 6126, 6116
// 7227, 7217
const int kAlpha = 26;
const lli kMod = 998244353;
const std::vector<std::string> kLastTwo = {"11", "12", "13", "14", "15",
                                           "16", "17", "18", "19", "21",
                                           "22", "23", "24", "25", "26"};

struct TestCase {
  std::string e;
  int k;
  std::string d;

  int Digit(const int i) { return d[i] - '0'; }
  std::vector<std::vector<lli>> memo;
  lli Count(int i = 0, int curr = 0) {
    if (i == d.size()) {
      return 1;
    }
    lli& ans = memo[i][curr];
    if (ans != -1) return ans;

    ans = 0;
    if (Digit(i)) ans = (ans + Count(i + 1, Digit(i))) % kMod;
    if (curr && curr * 10 + Digit(i) <= kAlpha)
      ans = (ans + Count(i + 1, curr * 10 + Digit(i))) % kMod;

    return ans;
  }

  std::set<std::string> all;
  void GenerateAll(std::string hehe, int i = 0) {
    if (i == hehe.size()) {
      all.insert(hehe);
      return;
    }

    if (hehe[i] == '?') {
      for (char c = '0'; c <= '9'; ++c) {
        hehe[i] = c;
        GenerateAll(hehe, i + 1);
      }
    } else {
      GenerateAll(hehe, i + 1);
    }
  }

  std::pair<std::string, lli> Solve() {
    std::cin >> e >> k;
    --k;

    d = e;
    DEBUG {
      GenerateAll(d);
      std::set<std::string> left;
      int best = 0;
      for (const auto& a : all) {
        // d = "7227";
        d = a;
        memo.resize(d.size(), std::vector<lli>(kAlpha + 1, -1));
        int curr = Count();
        if (curr > best) {
          left.clear();
          best = curr;
        }
        if (curr == best) {
          left.insert(d);
        }
        // break;
      }

      std::cout << "res: " << best << " " << left.size() << "\n";
      for (const auto& a : left) {
        std::cout << "\t" << a << "\n";
      }
    }
    else {
      bool is_first_question_limited = false;
      for (int i = d.size() - 1; i >= 0; --i) {
        if (d[i] != '?') continue;
        if (i + 1 < d.size() && d[i + 1] > '6')
          is_first_question_limited = true;
        break;
      }
      if (is_first_question_limited) ++k;

      bool last_is_question = d.back() == '?';

      if (last_is_question) {
        if (d.size() == 1) {
          d = '9' - k;
        } else if (d[d.size() - 2] == '1') {
          d.back() = "123456789"[8 - (k % 9)];
          k /= 9;
        } else if (d[d.size() - 2] == '2') {
          d.back() = "123456"[5 - (k % 6)];
          k /= 6;
        } else if (d[d.size() - 2] == '?') {
          d[d.size() - 2] = kLastTwo[14 - (k % 15)][0],
                       d.back() = kLastTwo[14 - (k % 15)][1];
          k /= 15;
        }
      }

      int question_index = 0;
      for (int i = d.size() - 1; i >= 0; --i) {
        // for (int i = 0; i < d.size(); ++i) {
        if (d[i] != '?') continue;

        const bool use_one = (k & (1 << question_index)) > 0;
        d[i] = use_one ? '1' : '2';
        ++question_index;
      }
    }

    memo.resize(d.size(), std::vector<lli>(kAlpha + 100, -1));
    return std::make_pair(d, Count());
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << ans.first << " " << ans.second
              << "\n";
  }
  return 0;
}