#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, ignore, k;
  std::string s;

  int CountWithoutOverlaps(const int sz, const std::vector<int>& positions) {
    int cnt = 0, last = -1;
    for (int i = 0; i < (int)positions.size(); ++i) {
      if (last == -1 || positions[i] - positions[last] >= sz) {
        ++cnt;
        last = i;
      }
      // int j = i;
      // while (j + 1 < (int)positions.size() &&
      //        positions[j + 1] - positions[j] < sz) {
      //   ++j;
      // }
      // cnt += ((j - i + 1 + 1) >> 1);
      // i = j;
    }
    return cnt;
  }
  int Solve(const int sz, const std::vector<int> curr) {
    std::array<std::vector<int>, 256> nxt_positions;
    for (const int pos : curr) {
      if (pos == n - 1) continue;
      nxt_positions[s[pos + 1]].push_back(pos + 1);
    }

    int ans = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      // DEBUG std::println("{}{} {} - {} - {}", std::string(sz + 1, '\t'), sz,
      //                    letter, nxt_positions[letter],
      //                    CountWithoutOverlaps(sz + 1,
      //                    nxt_positions[letter]));
      if (CountWithoutOverlaps(sz + 1, nxt_positions[letter]) < k) continue;
      ans = std::max(ans, 1 + Solve(sz + 1, nxt_positions[letter]));
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> ignore >> k)) return false;
    std::cin >> s;

    std::array<std::vector<int>, 256> positions;
    for (const auto [i, si] : s | std::views::enumerate) {
      positions[si].push_back(i);
    }
    int ans = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      // DEBUG std::println("{}{} - {}", std::string(1, '\t'), letter,
      //                    positions[letter]);
      if (positions[letter].size() < k) continue;
      ans = std::max(ans, 1 + Solve(1, positions[letter]));
    }
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
