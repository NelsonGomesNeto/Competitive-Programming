#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

void PrintMat(const std::vector<std::string>& mat) {
  for (const auto& row : mat) std::cout << row << std::endl;
}

std::vector<std::string> universe;
std::vector<bool> empty_rows, empty_cols;
int n, m;

const int di[4] = {0, 0, 1, -1};
const int dj[4] = {1, -1, 0, 0};
lli BfsSum(const std::vector<std::string>& mat, const int si, const int sj) {
  lli ans = 0;

  std::vector<std::vector<bool>> visited(mat.size(), std::vector<bool>(mat[0].size()));

  std::queue<std::tuple<std::pair<int, int>, lli>> q;
  q.emplace(std::make_pair(si, sj), 0);
  while (!q.empty()) {
    auto [p, dist] = q.front();
    q.pop();
    const int i = p.first, j = p.second;

    if (visited[i][j]) continue;
    visited[i][j] = true;

    if (empty_rows[i]) dist += (int)1e6 - 1;
    if (empty_cols[j]) dist += (int)1e6 - 1;

    if (mat[i][j] == '#') ans += dist;

    for (int d = 0; d < 4; ++d) {
      const int ni = i + di[d], nj = j + dj[d];
      if (ni < 0 || nj < 0 || ni >= mat.size() || nj >= mat[i].size()) continue;
      q.emplace(std::make_pair(ni, nj), dist + 1);
    }
  }

  return ans;
}

lli SumShortestPaths(const std::vector<std::string>& mat) {
  lli ans = 0;
  for (int i = 0; i < mat.size(); ++i) {
    for (int j = 0; j < mat[i].size(); ++j) {
      if (mat[i][j] == '.') continue;
      ans += BfsSum(mat, i, j);
    }
  }
  return ans;
}

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    universe.push_back(line);
  }
  n = universe.size(), m = universe[0].size();
  PrintMat(universe);

  int rows_to_expand = 0;
  empty_rows = std::vector<bool>(n, false);
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < m; ++j) cnt += universe[i][j] == '#';
    if (cnt == 0) empty_rows[i] = true, ++rows_to_expand;
  }
  empty_cols = std::vector<bool>(m, false);
  int cols_to_expand = 0;
  for (int j = 0; j < m; ++j) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += universe[i][j] == '#';
    if (cnt == 0) empty_cols[j] = true, ++cols_to_expand;
  }

  lli ans = SumShortestPaths(universe) >> 1;
  std::cout << ans << std::endl;

  return 0;
}