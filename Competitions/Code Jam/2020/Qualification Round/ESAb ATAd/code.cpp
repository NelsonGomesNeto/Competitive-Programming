#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int q;
int getAt(int p)
{
  q++;
  printf("%d\n", p + 1); fflush(stdout);
  char response[2]; scanf(" %s", response);
  return response[0] - '0';
}
vector<pair<int, int>> cnt[2][2];
void fix()
{
  if (!(q && q % 10 == 0)) return;

  bool eq = false, diff = false;
  if (!cnt[0][0].empty())
  {
    int e = getAt(cnt[0][0][0].first);
    if (e == 1) swap(cnt[0][0], cnt[1][1]);
    eq = true;
  }
  if (!eq && !cnt[1][1].empty())
  {
    int e = getAt(cnt[1][1][0].first);
    if (e == 0) swap(cnt[0][0], cnt[1][1]);
    eq = true;
  }
  if (!cnt[0][1].empty())
  {
    int d = getAt(cnt[0][1][0].first);
    if (d == 1) swap(cnt[0][1], cnt[1][0]);
    diff = true;
  }
  if (!diff && !cnt[1][0].empty())
  {
    int d = getAt(cnt[1][0][0].first);
    if (d == 0) swap(cnt[0][1], cnt[1][0]);
    diff = true;
  }
  if (!eq || !diff) getAt(0);
}

int main()
{
  int t, b; scanf("%d %d", &t, &b);
  while (t--)
  {
    q = 0;
    string ans = "";
    for (int i = 0; i < b; i++) ans += '0';
    for (int l = 0; l < 2; l++) for (int r = 0; r < 2; r++) cnt[l][r].clear();

    for (int i = 0, j = b - 1; i < j; i++, j--)
    {
      fix();
      int l = getAt(i);
      int r = getAt(j);
      cnt[l][r].push_back({i, j});
    }
    fix();

    for (int l = 0; l < 2; l++)
      for (int r = 0; r < 2; r++)
        for (auto p: cnt[l][r])
          ans[p.first] = '0' + l, ans[p.second] = '0' + r;

    printf("%s\n", ans.c_str()); fflush(stdout);
    char response[2]; scanf(" %s", response);
  }
  return 0;
}