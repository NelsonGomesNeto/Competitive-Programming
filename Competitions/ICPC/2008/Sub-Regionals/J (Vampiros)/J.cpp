#include <bits/stdc++.h>
#define lli long long int
#define ldouble long double
using namespace std;

int ev1, ev2, at, d;

map<pair<int, int>, int> stateId;
void dfs(int v1 = ev1, int v2 = ev2)
{
  if (stateId.count({v1, v2})) return;
  stateId[{v1, v2}] = stateId.size();
  if (v1 <= 0 || v2 <= 0) return;
  dfs(v1 - d, v2 + d), dfs(v1 + d, v2 - d);
}
vector<vector<ldouble>> matrix;
void matrixMult(vector<vector<ldouble>> &a, vector<vector<ldouble>> &b)
{
  vector<vector<ldouble>> ans = a;
  for (int i = 0; i < ans.size(); i ++) for (int j = 0; j < ans[0].size(); j ++) ans[i][j] = 0;
  for (int i = 0; i < a.size(); i ++)
    for (int j = 0; j < b[0].size(); j ++)
      for (int k = 0; k < a[0].size(); k ++)
        ans[i][j] += a[i][k] * b[k][j];
  a = ans;
}
void matrixExp(vector<vector<ldouble>> &x, lli y)
{
  vector<vector<ldouble>> ans = x;
  for (int i = 0; i < ans.size(); i ++) for (int j = 0; j < ans[0].size(); j ++) ans[i][j] = i == j;
  while (y)
  {
    if (y & 1LL) matrixMult(ans, x);
    matrixMult(x, x), y >>= 1LL;
  }
  x = ans;
}

int main()
{
  while (scanf("%d %d %d %d", &ev1, &ev2, &at, &d) != EOF && !(!ev1 && !ev2 && !at && !d))
  {
    // Gambler's Ruin solution:
      // ev1 = ceil((ldouble) ev1 / d), ev2 = ceil((ldouble) ev2 / d);
      // if (at == 3) // fair coin
      //   printf("%.1Lf\n", 100 * (ldouble) ev1 / (ev1 + ev2));
      // else // unfair coin
      // {
      //   ldouble p = (ldouble) at / 6, q = 1 - (ldouble) at / 6;
      //   printf("%.1Lf\n", 100 * (ldouble) (1 - pow(q / p, ev1)) / (1 - pow(q / p, ev1 + ev2)));
      // }
    // Markov Chain solution:
      matrix.clear(), stateId.clear();
      ldouble p = (ldouble) at / 6, q = 1 - (ldouble) at / 6;
      // Hard way to build the matrix:
        // dfs();
        // matrix.resize(stateId.size());
        // for (int i = 0; i < stateId.size(); i ++)
        //   matrix[i].resize(stateId.size());
        // for (auto &s: stateId)
        // {
        //   printf("%d\n", s.second);
        //   if (s.first.first > 0 && s.first.second > 0)
        //     matrix[s.second][stateId[{s.first.first + d, s.first.second - d}]] = p,
        //     matrix[s.second][stateId[{s.first.first - d, s.first.second + d}]] = q;
        //   else
        //     matrix[s.second][s.second] = 1;
        // }
      // Easy way to build the matrix:
        matrix.resize(ev1 + ev2 + 1);
        for (int i = 0; i <= ev1 + ev2; i ++)
          matrix[i].resize(ev1 + ev2 + 1);
        matrix[0][0] = matrix[ev1 + ev2][ev1 + ev2] = 1;
        for (int i = 1; i < ev1 + ev2; i ++)
          matrix[i][min(ev1 + ev2, i + d)] = p,
          matrix[i][max(0, i - d)] = q;

      matrixExp(matrix, 1000);
      // Hard way answer extration:
        // int initialState = 0, winState;
        // for (auto &s: stateId)
        //   if (s.first.second <= 0)
        //     winState = s.second;
        // printf("%.1Lf\n", 100*matrix[initialState][winState]);
      // Easy way answer extraction:
        printf("%.1Lf\n", 100*matrix[ev1][ev1 + ev2]);
  }
  return(0);
}