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

    assert(++queries <= kMaxQueries);
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
    kMaxQueries = std::max(n, 4);

    int res = n - 1;
    for (int i = 1; i < n; i += 2) {
      const int rem = (n - 1) - (i - 1) + 1;
      if (rem > 5 || rem == 3) {
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
      } else if (rem == 4) {
        const int a = i - 1, b = i, c = n - 2, d = n - 1;
        const int ab = Query(a, b), ba = Query(b, a);
        const int ac = Query(a, c), ca = Query(c, a);
        if (ab != ba) {
          if (ac != ca)
            res = a;
          else
            res = b;
        } else {
          if (ac != ca)
            res = c;
          else
            res = d;
        }
        break;
      } else if (rem == 5) {
        const int a = i - 1, b = i, c = n - 3, d = n - 2, e = n - 1;
        const int ab = Query(a, b), bc = Query(b, c), ca = Query(c, a);
        if (~(!ab + !bc + !ca) & 1) {
          // Impostor is d or e
          const int cd = Query(c, d), dc = Query(d, c);
          if (cd == dc)
            res = e;
          else
            res = d;
        } else {
          // Impostor is a, b, c
          const int ba = Query(b, a), ac = Query(a, c);
          if (ab != ba) {
            if (ac != ca)
              res = a;
            else
              res = b;
          } else {
            res = c;
          }
        }
        break;
      }
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
