#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int n, m;
std::vector<std::string> mat, path;
void PrintMat(const std::vector<std::string>& a) {
  for (const auto& row : a) {
    std::cout << row << std::endl;
  }
}

const char start = 'S', horizontal = '-', vertical = '|';
const char ur = 'L', ul = 'J', dl = '7', dr = 'F';
const std::set<char> border = {vertical, ur, ul, dl, dr, start};
// R, U, D, L
const int di[4] = {0, -1, 1, 0};
const int dj[4] = {1, 0, 0, -1};
const int opposite_dir[4] = {3, 2, 1, 0};
std::vector<int> dir_by_piece[256];
const std::set<char> possible[4] = {{start, horizontal, ul, dl},
                                    {start, vertical, dl, dr},
                                    {start, vertical, ul, ur},
                                    {start, horizontal, ur, dr}};
const std::map<std::set<int>, char> missing_piece = {
    {{0, 1}, ur},       {{0, 2}, dr}, {{0, 3}, horizontal},
    {{1, 2}, vertical}, {{1, 3}, ul}, {{2, 3}, dl}};
const std::set<std::set<char>> vertical_wall = {{ur, dl}, {ul, dr}};

int Bfs(const int si, const int sj) {
  std::queue<std::tuple<std::pair<int, int>, int, int>> q;

  std::set<int> s_connections;
  for (int d = 0; d < 4; ++d) {
    const int ni = si + di[d], nj = sj + dj[d];
    if (ni < 0 || nj < 0 || ni >= n || nj >= m ||
        !possible[d].count(mat[ni][nj]))
      continue;
    s_connections.insert(d);
    if (q.empty()) {
      q.emplace(std::make_pair(ni, nj), opposite_dir[d], 0);
    }
  }
  {
    auto it = missing_piece.find(s_connections);
    assert(it != missing_piece.end());
    path[si][sj] = it->second;
  }

  while (!q.empty()) {
    auto [p, forbidden_dir, dist] = q.front();
    q.pop();
    const int i = p.first, j = p.second;
    DEBUG std::cout << i << "," << j << " " << forbidden_dir << " " << dist
                    << std::endl;
    if (i == si && j == sj) return dist;
    path[i][j] = mat[i][j];

    for (const int d : dir_by_piece[mat[i][j]]) {
      if (d == forbidden_dir) continue;
      const int ni = i + di[d], nj = j + dj[d];
      if (ni < 0 || nj < 0 || ni >= n || nj >= m ||
          !possible[d].count(mat[ni][nj]))
        continue;
      q.emplace(std::make_pair(ni, nj), opposite_dir[d], dist + 1);
    }
  }
  assert(false);
  return -1;
}

int main() {
  dir_by_piece[horizontal] = {0, 3};
  dir_by_piece[vertical] = {1, 2};
  dir_by_piece[ur] = {1, 0};
  dir_by_piece[ul] = {1, 3};
  dir_by_piece[dr] = {2, 0};
  dir_by_piece[dl] = {2, 3};

  for (std::string line; std::getline(std::cin, line);) {
    mat.push_back(line);
  }
  path = mat;
  for (auto& row : path)
    for (auto& c : row) c = '.';

  PrintMat(mat);
  std::cout << std::endl;

  n = mat.size(), m = mat[0].size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == 'S') {
        Bfs(i, j);
      }
    }
  }

  PrintMat(path);
  std::cout << std::endl;

  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < m; ++j) {
      if (path[i][j] == '.') {
        path[i][j] = cnt & 1 ? 'I' : 'O';
        continue;
      }

      const char start = path[i][j];

      if (start == vertical) {
        ++cnt;
        continue;
      }

      int k = j;
      while (k + 1 < m && path[i][k + 1] == horizontal) {
        ++k;
      }
      ++k;

      const char end = path[i][k];

      const bool is_vertical_wall = vertical_wall.count({start, end});
      DEBUG {
        std::cout << "Line: " << i << ", row: " << j << " || " << start << end
                  << " " << is_vertical_wall << std::endl;
      }

      if (is_vertical_wall) {
        ++cnt;
      }

      j = k;
    }
  }

  PrintMat(path);

  int ans = 0;
  for (const auto& row : path)
    for (const char c : row) ans += c == 'I';
  std::cout << ans << std::endl;

  return 0;
}
