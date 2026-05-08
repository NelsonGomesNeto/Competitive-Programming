#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int N;
struct TestCase {
  std::vector<int> a;
  std::vector<std::pair<int, int>> b;

  void PrintA(const std::string& prefix, const std::vector<int>& arr) {
    std::cout << prefix;
    for (const auto ai : arr) std::cout << ai << " ";
    std::cout << "(" << arr.size() << ")\n";
  }
  void PrintB(const std::string& prefix,
              const std::vector<std::pair<int, int>>& arr) {
    std::cout << prefix;
    for (const auto& [one_pos, size] : arr)
      std::cout << "(" << one_pos << ", " << size << ")" << " ";
    std::cout << "(" << arr.size() << ")\n";
  }

  int CircularFix(const int move, const int size) {
    return (move % size + size) % size;
  }

  bool Run() {
    if (!(std::cin >> N)) return false;
    a.resize(N);
    for (auto& ai : a) std::cin >> ai;

    int offset = 0;
    for (int i = 0; i < N; ++i) {
      int j = i;
      while (j + 1 < N && a[j + 1] == a[i] + (j + 1 - i)) ++j;
      // std::cout << i << " " << j << " | " << offset << "\n";
      // std::fflush(stdout);
      if (a[i] == 1) {
        b.emplace_back(i - offset, a[j]);
      } else {
        b.emplace_back(j + 1 - offset, a[j]);
      }
      offset = j + a[i];
      i = offset - 1;
    }

    DEBUG { PrintB("\nb: ", b); }

    std::vector<std::pair<int, int>> operations;
    if (b.back().first)
      operations.emplace_back(2, CircularFix(-b.back().first, b.back().second));
    operations.emplace_back(1, b.back().second);
    int sum_required = CircularFix(-b.back().first, b.back().second);
    for (int i = (int)b.size() - 2; i >= 0; --i) {
      const auto& [req, size] = b[i];
      const int x = CircularFix(-sum_required - req, size);
      operations.emplace_back(2, x);
      operations.emplace_back(1, size);
      sum_required += x;
    }
    std::reverse(operations.begin(), operations.end());

    const int operations_sum = [&]() {
      int ans = 0;
      for (const auto& [op, x] : operations) ans += op == 1 ? 1 : x;
      return ans;
    }();
    assert(operations_sum <= 2 * N);

    std::cout << operations_sum << "\n";
    for (const auto& [op, x] : operations) {
      if (op == 1)
        std::cout << 1 << " " << x << "\n";
      else {
        for (int i = 0; i < x; ++i) std::cout << 2 << "\n";
      }
    }

    DEBUG {
      std::vector<std::pair<int, int>> c;
      for (const auto& [op, x] : operations) {
        if (op == 1)
          c.emplace_back(0, x);
        else {
          for (auto& [one_pos, size] : c)
            one_pos = CircularFix(one_pos - x, size);
        }
      }
      PrintB("c: ", c);
      std::fflush(stdout);
      assert(b == c);
      std::vector<int> d;
      for (const auto& [one_pos, size] : c) {
        std::vector<int> perm;
        for (int i = 1; i <= size; ++i) perm.push_back(i);
        std::rotate(perm.rbegin(), perm.rbegin() + one_pos, perm.rend());
        d.insert(d.end(), perm.begin(), perm.end());
      }
      PrintA("a: ", a);
      PrintA("d: ", d);
      std::fflush(stdout);
      assert(a == d);
    }

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
