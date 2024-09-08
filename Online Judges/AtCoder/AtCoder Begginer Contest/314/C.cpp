#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, m;
char ss[maxN + 1];
string s, tmp;
int c[maxN];
vector<vector<int>> pos;

int main()
{
  while (~scanf("%d %d", &n, &m)) {
    pos.clear();
    pos.resize(m);
    scanf(" %s", ss);
    s = string(ss);
    tmp = s;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &c[i]);
      --c[i];
      pos[c[i]].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < pos[i].size(); ++j) {
        int nxt = pos[i][(j + 1) % pos[i].size()];
        int curr = pos[i][j];
        s[nxt] = tmp[curr];
      }

      for (int j : pos[i])
        tmp[j] = s[j];
    }

    printf("%s\n", s.c_str());
  }
  return 0;
}
