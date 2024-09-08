#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// D, R, U, L - Movement in the matrix.
// U, L, D, R - Tilt direction.
const int di[4] = {1, 0, -1, 0};
const int dj[4] = {0, 1, 0, -1};
bool Valid(const int i, const int j, const int n, const int m,
           const std::vector<std::string>& mat) {
  return i >= 0 && i < n && j >= 0 && j < m && mat[i][j] != '#';
}
bool Within(const int x, int l, int r) {
  if (l > r) std::swap(l, r);
  return x >= l && x <= r;
}
void Tilt(const int d, std::vector<std::string>& mat) {
  const int n = mat.size(), m = mat[0].size();

  /*
  All the checks on for loops are wrong
  */

  auto move = [&](int& i, int& j) {
    if (mat[i][j] == '#') {
      return;
    }

    int ei = i, ej = j, cnt = mat[i][j] == 'O';
    while (Valid(ei + di[d], ej + dj[d], n, m, mat)) {
      ei += di[d], ej += dj[d];
      cnt += mat[ei][ej] == 'O';
    }

    for (int ki = i, kj = j; Within(ki, i, ei) && Within(kj, j, ej); ki += di[d], kj += dj[d]) {
      mat[ki][kj] = cnt-- > 0 ? 'O' : '.';
    }

    i = ei, j = ej;
  };

  if (d == 0 || d == 2) {
    int i_start = 0, i_end = n - 1;
    if (d == 2) std::swap(i_start, i_end);

    for (int j = 0; j < m; ++j) {
      for (int i = i_start; Within(i, i_start, i_end); i += di[d]) {
        move(i, j);
      }
    }
  } else {
    int j_start = 0, j_end = m - 1;
    if (d == 3) std::swap(j_start, j_end);

    for (int i = 0; i < n; ++i) {
      for (int j = j_start; Within(j, j_start, j_end); j += dj[d]) {
        move(i, j);
      }
    }
  }
}

void PrintMat(const std::vector<std::string>& mat) {
  for (const auto& row : mat) std::cout << row << std::endl;
}

int TotalLoad(const std::vector<std::string>& mat) {
  const int n = mat.size(), m = mat[0].size();
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == 'O') ans += n - i;
    }
  }
  return ans;
}

const lli kCycles = 1e9;
std::vector<std::string> mat;
int n, m;

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    mat.push_back(line);
  }
  n = mat.size(), m = mat[0].size();

  std::map<std::vector<std::string>, int> memo;
  int start_loop_index, close_loop_index;
  for (int i = 0; i < 1e3; ++i) {
    for (int d = 0; d < 4; ++d) {
      Tilt(d, mat);
    }
    std::cout << i << " " << TotalLoad(mat) << std::endl;

    auto [it, new_state] = memo.try_emplace(mat, i);
    if (!new_state) {
      start_loop_index = it->second;
      close_loop_index = i - 1;
      break;
    }
  }

  const int cycle_size = close_loop_index - start_loop_index + 1;
  std::vector<std::vector<std::string>> cycle(cycle_size);
  for (auto& [m, i] : memo) {
    if (Within(i, start_loop_index, close_loop_index)) {
      cycle[i - start_loop_index] = m;
    }
  }
  lli rem = kCycles - start_loop_index;
  lli mult = ceil((double) rem / cycle_size);
  lli end = start_loop_index + mult * cycle_size;
  int dist = end - kCycles;
  int index = cycle.size() - dist - 1;
  int ans = TotalLoad(cycle[index]);
  std::cout << ans << std::endl;

  return 0;
}