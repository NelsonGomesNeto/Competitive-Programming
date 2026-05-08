#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  int queries = 0;
  int kMaxQueries;

  std::map<std::pair<int, int>, int> cache;

  int Query(const int a, const int b) {
    const auto ab = std::make_pair(a, b);
    auto it = cache.find(ab);
    if (it != cache.end()) return it->second;

    assert(++queries < kMaxQueries);
    std::cout << "? " << (a + 1) << " " << (b + 1) << "\n";
    std::fflush(stdout);
    int res;
    std::cin >> res;
    assert(res != -1);
    // if (res == -1) exit(0);
    return cache[ab] = res;
  }

  void Answer(const int res) {
    std::cout << "! " << (res + 1) << "\n";
    std::fflush(stdout);
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    if (n == -1) return false;
    kMaxQueries = n + 69;

    int res = n - 1;
    for (int i = 1; i < n; i += 2) {
      const int a = i - 1, b = i, c = i == 1 ? n - 1 : 0;
      const int ab = Query(a, b), ba = Query(b, a);
      if (ab == ba) continue;

      // Either a or b is the impostor
      const int bc = Query(b, c), cb = Query(c, b);

      if (bc == cb)
        res = a;
      else
        res = b;

      break;
    }
    Answer(res);

    return true;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    if (!test_case.Run()) break;
  }

  return 0;
}
