#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
int cnt[256];
char s[2][maxN + 1];
vector<int> pos[2][256];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    pos[0]['a'].clear(), pos[1]['a'].clear();
    pos[0]['b'].clear(), pos[1]['b'].clear();
    scanf(" %s\n%s", s[0], s[1]);
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < n; j ++)
      {
        pos[i][s[i][j]].push_back(j);
        cnt[s[i][j]] ++;
      }

    if ((cnt['a'] & 1) || (cnt['b'] & 1))
      printf("-1\n");
    else
    {
      vector<pair<int, int>> ans;
      /*
      aa or bb
      bb    aa
      1 step (i, i + 1)

      ab or ba
      ba    ab
      2 steps (i, i), (i, i + 1)

      solve all 1 step, and then 2 steps
      */

      list<int> pos[2]; // ab -> 0, ba -> 1
      for (int i = 0; i < n; i ++)
        if ((s[0][i] == 'a' && s[1][i] == 'b') || (s[0][i] == 'b' && s[1][i] == 'a'))
          pos[s[0][i] == 'b' && s[1][i] == 'a'].push_back(i);

      for (int i = 0; i < 2; i ++)
        while (pos[i].size() > 1)
        {
          ans.push_back({*pos[i].begin(), *next(pos[i].begin())});
          pos[i].pop_front(), pos[i].pop_front();
        }

      if (!pos[0].empty())
      {
        ans.push_back({*pos[0].begin(), *pos[0].begin()});
        ans.push_back({*pos[0].begin(), *pos[1].begin()});
      }

      printf("%d\n", (int) ans.size());
      for (auto &a: ans)
        printf("%d %d\n", a.first + 1, a.second + 1);
    }
  }
  return(0);
}