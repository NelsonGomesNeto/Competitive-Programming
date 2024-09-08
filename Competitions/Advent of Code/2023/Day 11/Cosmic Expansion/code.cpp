#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

void PrintMat(const std::vector<std::string>& mat) {
  for (const auto& row : mat) std::cout << row << std::endl;
}

std::vector<std::string> universe;
int n, m;

const int di[4] = {0, 0, 1, -1};
const int dj[4] = {1, -1, 0, 0};
int BfsSum(const std::vector<std::string>& mat, const int si, const int sj) {
  int ans = 0;

  std::vector<std::vector<bool>> visited(mat.size(), std::vector<bool>(mat[0].size()));

  std::queue<std::tuple<std::pair<int, int>, int>> q;
  q.emplace(std::make_pair(si, sj), 0);
  while (!q.empty()) {
    auto [p, dist] = q.front();
    q.pop();

    const int i = p.first, j = p.second;
    if (visited[i][j]) continue;
    visited[i][j] = true;

    if (mat[i][j] == '#') ans += dist;

    for (int d = 0; d < 4; ++d) {
      const int ni = i + di[d], nj = j + dj[d];
      if (ni < 0 || nj < 0 || ni >= mat.size() || nj >= mat[i].size()) continue;
      q.emplace(std::make_pair(ni, nj), dist + 1);
    }
  }

  return ans;
}

int SumShortestPaths(const std::vector<std::string>& mat) {
  int ans = 0;
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

  std::vector<bool> empty_rows(n, false);
  int rows_to_expand = 0;
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < m; ++j) cnt += universe[i][j] == '#';
    if (cnt == 0) empty_rows[i] = true, ++rows_to_expand;
  }
  std::vector<bool> empty_cols(m, false);
  int cols_to_expand = 0;
  for (int j = 0; j < m; ++j) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += universe[i][j] == '#';
    if (cnt == 0) empty_cols[j] = true, ++cols_to_expand;
  }

  std::vector<std::string> expanded_universe(n + rows_to_expand, std::string(m + cols_to_expand, '.'));
  for (int i = 0, ii = 0; i < n; ++i, ++ii) {
    if (empty_rows[i]) {
      ++ii;
      continue;
    }
    for (int j = 0, jj = 0; j < m; ++j, ++jj) {
      if (empty_cols[j]) {
        ++jj;
        continue;
      }
      expanded_universe[ii][jj] = universe[i][j];
    }
  }
  PrintMat(expanded_universe);

  int ans = SumShortestPaths(expanded_universe) >> 1;
  std::cout << ans << std::endl;

  return 0;
}