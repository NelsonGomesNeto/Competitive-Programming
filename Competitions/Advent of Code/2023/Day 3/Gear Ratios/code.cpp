#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 1e3;
char ss[kMaxN + 1];
int n;
string mat[kMaxN];

bool IsNumber(char a) {
  return a >= '0' && a <= '9';
}
bool IsSymbol(char a) {
  return !IsNumber(a) && a != '.';
}

bool HasAdjacentSymbol(int i, int loj, int hij) {
  for (int ci : {i - 1, i + 1}) {
    if (ci < 0 || ci >= n) continue;

    for (int j = max(0, loj - 1), end = min((int)mat[ci].size() - 1, hij + 1); j <= end; ++j) {
      if (IsSymbol(mat[ci][j])) {
        return true;
      }
    }
  }
  if (loj && IsSymbol(mat[i][loj - 1])) return true;
  if (hij + 1 < mat[i].size() && IsSymbol(mat[i][hij + 1])) return true;

  return false;
}

int main() {
  n = 0;
  for (int i = 0; ~scanf(" %s", ss); ++i, ++n) {
    mat[i] = string(ss);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < mat[i].size(); ++j) {
      if (!IsNumber(mat[i][j])) continue;

      int k = j;
      while (k + 1 < mat[i].size() && IsNumber(mat[i][k + 1])) {
        ++k;
      }

      if (!HasAdjacentSymbol(i, j, k)) continue;

      int part_number;
      sscanf(mat[i].substr(j, k - j + 1).c_str(), "%d", &part_number);
      ans += part_number;

      j = k;
    }
  }

  printf("%d\n", ans);
  return 0;
}
