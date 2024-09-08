#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Pattern {
  std::vector<std::string> mat;
  int n, m;

  int Reflection() const {
    for (int j = 0; j < m - 1; ++j) {
      int diffs = 0;

      for (int l = j, r = j + 1; diffs <= 1 && l >= 0 && r < m; --l, ++r) {
        for (int i = 0; i < n; ++i)
          if (mat[i][l] != mat[i][r]) {
            DEBUG std::cout << i << " " << l << " " << r << " " << mat[i][l]
                            << " " << mat[i][r] << std::endl;
            ++diffs;
          }
      }
      DEBUG std::cout << "Col: " << j << " is: " << diffs << std::endl;

      if (diffs == 1) return j + 1;
    }

    for (int i = 0; i < n - 1; ++i) {
      int diffs = 0;

      for (int l = i, r = i + 1; diffs <= 1 && l >= 0 && r < n; --l, ++r) {
        for (int j = 0; j < m; ++j)
          if (mat[l][j] != mat[r][j]) {
            ++diffs;
          }
      }

      if (diffs == 1) return 100 * (i + 1);
    }

    return 0;
  }

  friend std::istream& operator>>(std::istream& stream, Pattern& p) {
    p.mat.clear();
    for (std::string line; std::getline(stream, line);) {
      if (line.empty()) break;
      p.mat.push_back(line);
    }
    p.n = p.mat.size(), p.m = p.mat[0].size();
    return stream;
  }
};
std::vector<Pattern> patterns;

int main() {
  Pattern p;
  while (std::cin >> p) {
    patterns.push_back(p);
  }
  patterns.push_back(p);

  int ans = 0;
  for (const auto& pattern : patterns) {
    const int reflection = pattern.Reflection();
    ans += reflection;
    std::cout << "\t" << reflection << std::endl;
  }
  std::cout << ans << std::endl;

  return 0;
}