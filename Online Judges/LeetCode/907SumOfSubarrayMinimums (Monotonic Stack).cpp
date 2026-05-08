#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

using time_precision = std::chrono::milliseconds;

const int kMaxA = 3e4;
const lli kMod = 1e9 + 7;

class Solution {
 public:
  lli subarryCount(const int sz) {
    // 1 -> 1
    // 2 -> 3
    // 3 -> 6
    return sz * (sz + 1) >> 1;
  }
  struct PosValue {
    int pos, value;
  };
  int sumSubarrayMins(const std::vector<int>& arr) {
    const int n = (int)arr.size();

    std::vector<int> left_closest_smaller(n);
    {
      std::stack<PosValue> s;
      for (const auto [i, ai] : arr | std::views::enumerate) {
        while (!s.empty() && ai <= s.top().value) {
          s.pop();
        }
        left_closest_smaller[i] = s.empty() ? -1 : s.top().pos;
        s.emplace(i, ai);
      }
    }
    std::vector<int> right_closest_smaller_or_equal(n);
    {
      std::stack<PosValue> s;
      for (const auto [i, ai] :
           arr | std::views::enumerate | std::views::reverse) {
        while (!s.empty() && ai < s.top().value) {
          s.pop();
        }
        right_closest_smaller_or_equal[i] = s.empty() ? n : s.top().pos;
        s.emplace(i, ai);
      }
    }

    lli ans = 0;
    for (const auto [i, ai] : arr | std::views::enumerate) {
      const lli lo = left_closest_smaller[i] + 1,
                hi = right_closest_smaller_or_equal[i] - 1;
      const lli left = i - lo + 1, right = hi - i + 1;
      DEBUG std::println("\t{} {} | {} {} | {} {}", i, ai, lo, hi, left, right);
      ans = (ans + left * right % kMod * ai % kMod) % kMod;
    }

    return ans;
  }
};

struct TestCase {
  bool Run() {
    std::string line;
    if (!(std::getline(std::cin, line))) return false;
    std::istringstream linein(line);
    std::vector<int> arr;
    for (std::string num; std::getline(linein, num, ' ');) {
      arr.push_back(std::stoi(num));
    }
    const auto start = std::chrono::high_resolution_clock::now();
    const lli ans = Solution().sumSubarrayMins(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("\ttime: {}", duration);
    std::println("{}", ans);
    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
