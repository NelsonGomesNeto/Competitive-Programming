#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kBlinks = 75;

struct Problem {
  std::vector<lli> initial_stones;
  std::map<lli, lli> stones_cnt;

  int DigitCount(lli x) {
    int cnt = x == 0;
    while (x) {
      x /= 10, ++cnt;
    }
    return cnt;
  }
  lli GetLeftHalf(lli x, int digit_cnt) {
    while (digit_cnt--) x /= 10;
    return x;
  }
  lli GetRightHalf(lli x, const int digit_cnt) {
    return x - GetLeftHalf(x, digit_cnt) * std::pow(10, digit_cnt);
  }

  void Blink() {
    std::map<lli, lli> new_cnt;
    for (const auto& [a, cnt] : stones_cnt) {
      assert(DigitCount(a) <= 15);
      if (a == 0) {
        new_cnt[1] += cnt;
      } else if (const int digit_cnt = DigitCount(a); ~digit_cnt & 1) {
        new_cnt[GetLeftHalf(a, digit_cnt / 2)] += cnt;
        new_cnt[GetRightHalf(a, digit_cnt / 2)] += cnt;
      } else {
        new_cnt[a * 2024] += cnt;
      }
    }
    stones_cnt = new_cnt;
  }

  void PrintStones() {
    for (const auto& [a, cnt] : stones_cnt) {
      std::cout << "(" << a << ", " << cnt << ") ";
    }
    std::cout << "\n";
  }

  void Solve() {
    for (lli a; std::cin >> a;) {
      initial_stones.push_back(a);
    }
    for (const lli a : initial_stones) stones_cnt[a]++;
    DEBUG PrintStones();

    for (int i = 0; i < kBlinks; ++i) {
      Blink();
      std::cout << "\t" << stones_cnt.size() << "\n";
      assert(stones_cnt.size() < (int)1e7);
      DEBUG PrintStones();
    }

    lli ans = 0;
    for (const auto& [a, cnt] : stones_cnt) ans += cnt;
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
