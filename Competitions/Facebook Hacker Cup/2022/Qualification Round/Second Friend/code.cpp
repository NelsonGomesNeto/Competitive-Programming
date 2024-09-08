#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n, m;
char s[maxN + 1];
string canvas[maxN];

int di[4] = {1, 0, -1, 0}, dj[4] = {0, 1, 0, -1};

int treeFriends(int i, int j) {
  int cnt = 0;
  for (int d = 0; d < 4; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    cnt += ni >= 0 && nj >= 0 && ni < n && nj < m && canvas[ni][nj] == '^';
  }
  return cnt;
}

void dfs(int i, int j) {
  if (i < 0 || j < 0 || i >= n || j >= m || canvas[i][j] != '.') return;
  canvas[i][j] = '^';

  for (int d = 0; d < 4; ++d)
    dfs(i + di[d], j + dj[d]);

  if (treeFriends(i, j) < 2)
    canvas[i][j] = '.';
}

int main() {
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
      canvas[i].clear();
      scanf(" %s", s);
      canvas[i] = string(s);
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (canvas[i][j] == '^') {
          canvas[i][j] = '.';
          dfs(i, j);
          canvas[i][j] = '^';
        }

    bool can = true;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (canvas[i][j] == '^' && treeFriends(i, j) < 2)
          can = false;

    printf("Case #%d: %s\n", testCase, can ? "Possible" : "Impossible");
    if (can)
      for (int i = 0; i < n; ++i)
        printf("%s\n", canvas[i].c_str());
  }
  return 0;
}
