#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<lli> a, tmp;
  std::unordered_set<lli> possible;

  lli xor_sum;
  std::vector<lli> groups;
  void BruteForce(int i, int gi) {
    if (i == a.size()) {
      possible.insert(xor_sum);
      return;
    }

    for (int j = 0; j <= gi; ++j) {
      xor_sum ^= groups[j] ^ (groups[j] + a[i]);
      groups[j] += a[i];
      BruteForce(i + 1, j == gi ? gi + 1 : gi);
      groups[j] -= a[i];
      xor_sum ^= (groups[j] + a[i]) ^ groups[j];
    }
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    xor_sum = 0;
    for (auto& ai : a) {
      std::cin >> ai;
      xor_sum ^= ai;
    }

    groups.resize(n, 0);
    BruteForce(0, 0);

    // for (auto& pi : possible) {
    //   std::cout << "\t" << pi << "\n";
    // }
    std::cout << possible.size() << "\n";

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
