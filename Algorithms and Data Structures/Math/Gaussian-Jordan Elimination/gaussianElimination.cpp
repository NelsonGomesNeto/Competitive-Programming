#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

namespace GaussianElimination {
const double kEps = 1e-12;
enum Solutions { kZero, kOne, kInf };
Solutions Solve(std::vector<std::vector<double>> a, std::vector<double>& ans,
                std::vector<int>& free_variables) {
  int n = a.size(), m = a[0].size() - 1;

  std::vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int sel = row;
    for (int i = row; i < n; i++)
      if (std::abs(a[i][col]) > std::abs(a[sel][col])) sel = i;

    if (std::abs(a[sel][col]) < kEps) continue;

    for (int j = col; j <= m; j++) std::swap(a[sel][j], a[row][j]);
    where[col] = row;

    for (int i = 0; i < n; i++)
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }

    row++;
  }

  ans.resize(m, 0);
  for (int i = 0; i < m; i++)
    if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < m; j++) sum += ans[j] * a[i][j];
    if (std::abs(sum - a[i][m]) > kEps) return kZero;
  }

  free_variables.clear();
  Solutions solutions = kOne;
  for (int i = 0; i < m; i++) {
    if (where[i] == -1) {
      printf("\tindependent variable: %d\n", i);
      solutions = kInf;
      free_variables.push_back(i);
    }
  }
  return solutions;
}
}  // namespace GaussianElimination

const int maxN = 1e2;
int n, m;
std::vector<std::vector<double>> mat;
std::vector<double> ans;

int main() {
  while (scanf("%d %d", &n, &m) != EOF) {
    mat.resize(n, std::vector<double>(m + 1));
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= m; j++) scanf("%lf", &mat[i][j]);

    std::vector<int> free_variables;
    int solutions = GaussianElimination::Solve(mat, ans, free_variables);
    printf("Solutions: %s\n", solutions == GaussianElimination::kZero  ? "ZERO"
                              : solutions == GaussianElimination::kOne ? "ONE"
                                                                       : "INF");
    for (int i = 0; i < m; i++) printf("x_%d: %lf\n", i, ans[i]);
  }
  return 0;
}