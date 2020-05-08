#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

int cnt[16][256];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    memset(cnt, 0, sizeof(cnt));
    int u; scanf("%d", &u);
    for (int i = 0; i < 1e4; i++)
    {
      lli m; char r[17];
      scanf("%lld %s", &m, r);
      int size = strlen(r);
      for (int j = size - 1, d = 0; j >= 0; j--, d++)
        cnt[j][r[j]]++;
    }
    set<char> d;
    for (int i = 'A'; i <= 'Z'; i++)
    {
      bool has = false;
      for (int j = 0; j < 16; j++)
        if (cnt[j][i] != 0)
          has = true;
      DEBUG
      if (has)
      {
        printf("%c - ", i);
        for (int j = 0; j < 16; j++)
          printf("(%2d, %5d) ", j, cnt[j][i]);
        printf("\n");
      }
      if (has) d.insert(i);
    }

    string ans = "";
    for (char l: d)
      if (cnt[0][l] == 0)
      {
        ans += l;
        break;
      }
    d.erase(ans[0]);

    vector<pair<int, char>> total;
    for (char l: d)
    {
      int tot = 0;
      for (int i = 0; i < 1; i++) tot += cnt[i][l];
      total.push_back({tot, l});
    }
    sort(total.begin(), total.end());
    reverse(total.begin(), total.end());

    for (auto p: total)
      ans += p.second;
    // reverse(ans.begin() + 1, ans.end());

    printf("Case #%d: %s\n", tt, ans.c_str());
  }
  return 0;
}