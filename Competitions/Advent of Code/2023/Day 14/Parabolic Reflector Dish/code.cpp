#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double

void TiltUp(std::vector<std::string>& mat) {
  const int n = mat.size(), m = mat[0].size();
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (mat[i][j] == '#') continue;

      int ei = i, cnt = mat[i][j] == 'O';
      while (ei + 1 < n && mat[ei + 1][j] != '#') {
        ++ei;
        cnt += mat[ei][j] == 'O';
      }

      for (int k = i; k <= ei; ++k) {
        mat[k][j] = cnt-- > 0 ? 'O' : '.';
      }

      i = ei;
    }
  }
}

void PrintMat(const std::vector<std::string>& mat) {
  for (const auto& row : mat) std::cout << row << std::endl;
}

std::vector<std::string> mat;
int n, m;


int main() {
  for (std::string line; std::getline(std::cin, line);) {
    mat.push_back(line);
  }
  n = mat.size(), m = mat[0].size();

  TiltUp(mat);

  PrintMat(mat);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == 'O')
        ans += n - i;
    }
  }
  std::cout << ans << std::endl;

  return 0;
}