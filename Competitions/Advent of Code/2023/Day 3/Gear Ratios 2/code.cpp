#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 1e3;
char ss[kMaxN + 1];
int n;
string mat[kMaxN];

map<pair<int, int>, vector<lli>> gear_to_part_numbers;

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
vector<pair<int, int>> FindAdjacentGears(int i, int loj, int hij) {
  vector<pair<int, int>> gears;

  for (int ci : {i - 1, i + 1}) {
    if (ci < 0 || ci >= n) continue;

    for (int j = max(0, loj - 1), end = min((int)mat[ci].size() - 1, hij + 1); j <= end; ++j) {
      if (mat[ci][j] == '*') {
        gears.emplace_back(ci, j);
      }
    }
  }
  if (loj && mat[i][loj - 1] == '*') gears.emplace_back(i, loj - 1);
  if (hij + 1 < mat[i].size() && mat[i][hij + 1] == '*') gears.emplace_back(i, hij + 1);

  return gears;
}

int main() {
  n = 0;
  for (int i = 0; ~scanf(" %s", ss); ++i, ++n) {
    mat[i] = string(ss);
  }

  lli ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < mat[i].size(); ++j) {
      if (!IsNumber(mat[i][j])) continue;

      int k = j;
      while (k + 1 < mat[i].size() && IsNumber(mat[i][k + 1])) {
        ++k;
      }

      if (!HasAdjacentSymbol(i, j, k)) continue;

      lli part_number;
      sscanf(mat[i].substr(j, k - j + 1).c_str(), "%lld", &part_number);
      // ans += part_number;

      vector<pair<int, int>> adjacent_gears = FindAdjacentGears(i, j, k);
      for (const auto pos : adjacent_gears) {
        gear_to_part_numbers[pos].push_back(part_number);
      }

      j = k;
    }
  }

  for (auto [pos, part_numbers] : gear_to_part_numbers) {
    if (part_numbers.size() == 2) {
      ans += (lli)part_numbers[0] * part_numbers[1];
    }
  }

  printf("%lld\n", ans);
  return 0;
}
