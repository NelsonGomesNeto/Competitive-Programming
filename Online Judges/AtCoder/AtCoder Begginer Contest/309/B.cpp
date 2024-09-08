#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2;
int n;
char a[maxN][maxN + 1];
char tmp[maxN][maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf(" %s", a[i]);
    memcpy(tmp, a, sizeof(a));

    vector<pair<int, int>> outer;
    for (int j = 0; j < n; ++j) outer.push_back(make_pair(0, j));
    for (int i = 1; i < n; ++i) outer.push_back(make_pair(i, n - 1));
    for (int j = 1; j < n; ++j) outer.push_back(make_pair(n - 1, n - 1 - j));
    for (int i = 1; i < n - 1; ++i) outer.push_back(make_pair(n - 1 - i, 0));

    for (int o = 0; o < outer.size(); ++o)
    {
      auto [i, j] = outer[o];
      auto [ni, nj] = outer[(o + 1) % outer.size()];
      DEBUG printf("%d %d - %d %d\n", i + 1, j + 1, ni + 1, nj + 1);
      a[ni][nj] = tmp[i][j];
    }

    for (int i = 0; i < n; ++i)
      printf("%s\n", a[i]);
  }
  return 0;
}
