#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kBlinks = 25;

struct Problem {
  std::vector<lli> initial_stones;
  std::list<lli> stones;

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

  void Blink2() {
    std::list<lli> new_stones;
    for (auto it = stones.begin(); it != stones.end(); ++it) {
      assert(DigitCount(*it) <= 15);
      if (*it == 0) {
        *it = 1;
        new_stones.push_back(*it);
      } else if (const int digit_cnt = DigitCount(*it); ~digit_cnt & 1) {
        new_stones.push_back(GetLeftHalf(*it, digit_cnt / 2));
        new_stones.push_back(GetRightHalf(*it, digit_cnt / 2));
      } else {
        *it *= 2024;
        new_stones.push_back(*it);
      }
    }
    stones = new_stones;
  }
  void Blink() {
    for (auto it = stones.begin(); it != stones.end();) {
      assert(DigitCount(*it) <= 15);
      if (*it == 0) {
        *it = 1;
        ++it;
      } else if (const int digit_cnt = DigitCount(*it); ~digit_cnt & 1) {
        stones.insert(it, GetLeftHalf(*it, digit_cnt / 2));
        stones.insert(it, GetRightHalf(*it, digit_cnt / 2));
        it = stones.erase(it);
      } else {
        *it *= 2024;
        ++it;
      }
    }
  }

  void PrintStones() {
    for (auto it = stones.begin(); it != stones.end(); ++it) {
      if (it != stones.begin()) std::cout << " ";
      std::cout << *it;
    }
    std::cout << "\n";
    std::fflush(stdout);
  }

  void Solve() {
    for (lli a; std::cin >> a;) {
      initial_stones.push_back(a);
    }
    stones = std::list<lli>(initial_stones.begin(), initial_stones.end());
    DEBUG PrintStones();

    for (int i = 0; i < kBlinks; ++i) {
      Blink();
      assert(stones.size() < (int)1e8);
      DEBUG PrintStones();
    }

    const int ans = (int)stones.size();
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
