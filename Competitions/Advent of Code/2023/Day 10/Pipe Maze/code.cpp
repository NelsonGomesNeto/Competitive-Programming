#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int n, m;
std::vector<std::string> mat;
void PrintMat() {
  for (const auto& row : mat) {
    std::cout << row << std::endl;
  }
}

const char start = 'S', horizontal = '-', vertical = '|';
const char ur = 'L', ul = 'J', dl = '7', dr = 'F';
// R, U, D, L
const int di[4] = {0, -1, 1, 0};
const int dj[4] = {1, 0, 0, -1};
const int opposite_dir[4] = {3, 2, 1, 0};
std::vector<int> dir_by_piece[256];
const std::set<char> possible[4] = {{start, horizontal, ul, dl},
                                    {start, vertical, dl, dr},
                                    {start, vertical, ul, ur},
                                    {start, horizontal, ur, dr}};

int Bfs(const int si, const int sj) {
  std::queue<std::tuple<std::pair<int, int>, int, int>> q;
  for (int d = 0; d < 4; ++d) {
    const int ni = si + di[d], nj = sj + dj[d];
    if (ni < 0 || nj < 0 || ni >= n || nj >= m ||
        !possible[d].count(mat[ni][nj]))
      continue;
    q.emplace(std::make_pair(ni, nj), opposite_dir[d], 0);
    break;
  }
  std::set<std::pair<int, int>> visited;

  while (!q.empty()) {
    auto [p, forbidden_dir, dist] = q.front();
    q.pop();
    const int i = p.first, j = p.second;
    DEBUG std::cout << i << "," << j << " " << forbidden_dir << " " << dist
                    << std::endl;
    if (i == si && j == sj) return dist;

    for (const int d : dir_by_piece[mat[i][j]]) {
      if (d == forbidden_dir) continue;
      const int ni = i + di[d], nj = j + dj[d];
      if (ni < 0 || nj < 0 || ni >= n || nj >= m ||
          !possible[d].count(mat[ni][nj]))
        continue;
      q.emplace(std::make_pair(ni, nj), opposite_dir[d], dist + 1);
    }

    mat[i][j] = '*';
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

  PrintMat();

  n = mat.size(), m = mat[0].size();
  int ans;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == 'S') {
        ans = (Bfs(i, j) + 1) / 2;
      }
    }
  }
  std::cout << ans << std::endl;

  PrintMat();

  return 0;
}
