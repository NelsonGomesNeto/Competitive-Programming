#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::string> mat;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    mat.resize(n);
    for (auto& line : mat) std::cin >> line;

    int loj = 0;
    for (int j = 0; j < m; ++j) {
      const bool has = [&]() {
        for (int i = 0; i < n; ++i) {
          if (mat[i][j] == '#') return true;
        }
        return false;
      }();
      if (has) break;
      loj = j + 1;
    }
    int hij = m - 1;
    for (int j = m - 1; j >= 0; --j) {
      const bool has = [&]() {
        for (int i = 0; i < n; ++i) {
          if (mat[i][j] == '#') return true;
        }
        return false;
      }();
      if (has) break;
      hij = j - 1;
    }

    int loi = 0;
    for (int i = 0; i < n; ++i) {
      if (std::ranges::contains(mat[i], '#')) break;
      loi = i + 1;
    }
    int hii = n - 1;
    for (int i = n - 1; i >= 0; --i) {
      if (std::ranges::contains(mat[i], '#')) break;
      hii = i - 1;
    }

    DEBUG std::println("{} {} | {} {}", loi, hii, loj, hij);

    for (int i = loi; i <= hii; ++i) {
      std::println("{}", mat[i].substr(loj, hij - loj + 1));
    }

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
