#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxN = 5e3;
const int kMaxA = 2e5;
std::vector<int> kNil = {0, 0, 0};
std::vector<std::vector<int>> kVitamins = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

struct TestCase {
  int n, x;
  struct Food {
    int v, a, c;
    std::vector<int> GetVitamin() const { return kVitamins[v - 1]; }
    bool operator<(const Food& other) const { return v < other.v; }
  };
  std::vector<Food> foods;
  std::vector<std::vector<Food>> foods_by_vitamin;
  int GetMin(const std::vector<int> a) { return *std::ranges::min_element(a); }
  int GetSum(const std::vector<int> a) {
    int sum = 0;
    for (const auto& ai : a) sum += ai;
    return sum;
  }

  std::vector<std::vector<std::vector<int>>> memo;
  int MaximizeVitamins(int vi, int i, int budget) {
    if (i == foods_by_vitamin[vi].size() || budget == 0) {
      return 0;
    }
    int& ans = memo[vi][i][budget];
    if (ans != -1) return ans;

    ans = MaximizeVitamins(vi, i + 1, budget);
    if (budget >= foods_by_vitamin[vi][i].c)
      ans = std::max(
          ans, MaximizeVitamins(vi, i + 1, budget - foods_by_vitamin[vi][i].c) +
                   foods_by_vitamin[vi][i].a);

    return ans;
  }
  int MinimizeCalories(const int vi, const lli target) {
    int lo = 0, hi = x;
    while (lo < hi) {
      int mid = (lo + hi) >> 1;
      if (MaximizeVitamins(vi, 0, mid) >= target)
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
  bool Can(const lli mini) {
    int calories = x;
    for (int i = 0; i < 3; ++i) {
      int cal = MinimizeCalories(i, mini);
      calories -= cal;
      if (calories < 0) return false;
    }
    return true;
  }

  bool Run() {
    if (!(std::cin >> n >> x)) return false;
    foods.resize(n);
    foods_by_vitamin.resize(3, {});
    for (auto& fi : foods) {
      std::cin >> fi.v >> fi.a >> fi.c;
      foods_by_vitamin[fi.v - 1].push_back(fi);
    }

    memo.resize(3,
                std::vector<std::vector<int>>(n, std::vector<int>(x + 1, -1)));
    lli lo = 0, hi = (lli)kMaxN * kMaxA;
    while (lo < hi) {
      lli mid = (lo + hi + 1) >> 1;
      if (Can(mid))
        lo = mid;
      else
        hi = mid - 1;
    }
    int ans = lo;
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
