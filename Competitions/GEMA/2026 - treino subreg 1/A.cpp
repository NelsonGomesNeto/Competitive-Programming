#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxN = 100;
const int kMaxA = 2e3;
const int kMaxTarget = (kMaxN * kMaxA) >> 1;
using all_sums_bitset = std::bitset<kMaxTarget + 1>;

struct TestCase {
  int n;
  std::vector<int> a;

  std::array<std::array<int, kMaxTarget + 1>, kMaxN> memo;
  bool SubsetSum(const std::vector<int>& arr, const int target,
                 const int i = 0) {
    if (target == 0) return true;
    if (i == (int)arr.size()) return false;
    int& res = memo[i][target];
    if (res != -1) return res;
    res = false;
    if (arr[i] <= target) res = SubsetSum(arr, target - arr[i], i + 1);
    return res = (res || SubsetSum(arr, target, i + 1));
  }
  bool SubsetSumBitSet(const std::vector<int>& arr, const int target) {
    all_sums_bitset curr = 1;
    for (const auto ai : arr) curr |= curr << ai;
    return curr[target];
  }

  bool IsGood(const std::vector<int>& arr) {
    const int sz = arr.size();
    const int sum = std::reduce(arr.begin(), arr.end(), 0, std::plus());
    if (sum & 1) return true;

    const int target = sum >> 1;
    // for (int i = 0; i < sz; ++i) {
    //   std::ranges::fill(memo[i], -1);
    // }
    // std::println("\t\t{} {}", target, SubsetSum(arr, target));
    // return !SubsetSum(arr, target);
    return !SubsetSumBitSet(arr, target);
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    if (IsGood(a)) {
      std::println("0");
      return true;
    } else {
      std::vector<int> b;
      for (int i = 0; i < n; ++i) {
        b = a;
        b.erase(b.begin() + i);
        // std::println("\t{}", b);
        if (IsGood(b)) {
          std::println("1\n{}", i + 1);
          return true;
        }
      }
    }
    assert(false);

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
