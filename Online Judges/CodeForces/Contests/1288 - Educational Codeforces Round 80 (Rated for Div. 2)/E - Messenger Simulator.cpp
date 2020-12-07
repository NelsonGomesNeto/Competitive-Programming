#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m;
int a[maxN];
int ans[2][maxN], pos[maxN], rep[maxN];
vector<int> nums;
vector<int> pos[maxN];

int main()
{
  int t = 0;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    if (t ++) printf("-------\n");

    memset(ans, 0, sizeof(ans));
    memset(pos, -1, sizeof(pos));
    nums.clear();

    for (int i = 0; i < m; i ++)
    {
      scanf("%d", &a[i]);
      a[i] --;
      pos[a[i]].push_back(i);
    }

    for (int i = 0; i < m; i ++)
    {
      scanf("%d", &a[i]); a[i] --;
    }
    for (int i = 0; i < n; i ++)
      acc[i + 1] = acc[i] + !pos[i].empty();
 
    for (int i = 0; i < n; i ++)
      if (pos[i].empty())
      {
        ans[0][i] = i + 1;
        ans[1][i] = min(n, i + 1 + acc[n] - acc[i]);
      }
      else
      {
        ans[0][i] = 1;
        ans[1][i] = min(n, max(ans[1][i], m - pos[i].back() - (int)pos[i].size() + 1));
        for (int j = 0; j < pos[i].size() - 1; j ++)
          ans[1][i] = min(n, max(ans[1][i], pos[i][j + 1] - pos[i][j] + 1));
      }
 
  
    for (int i = m - 1, at = 0; i >= 0; i --, at ++)
    {
      if (at) rep[at] = rep[at - 1];
  
      if (pos[a[i]] != -1)
      {
        ans[1][a[i]] = max(ans[1][a[i]], at - pos[a[i]] + 1 - (rep[at] - rep[pos[a[i]] + 1]));
        rep[at] ++;
      }
      pos[a[i]] = at;
      nums.push_back(a[i]);
    }
    for (int i = 0; i < n; i ++)
      if (pos[i] == -1)
        nums.push_back(i);
    bool done[n]; memset(done, false, sizeof(done));
    for (int i = nums.size() - 1, at = n + 1; i >= 0; i --)
    {
      if (!done[nums[i]])
        at -= done[nums[i]] = true;
      ans[1][nums[i]] = max(ans[1][nums[i]], at);
    }

    for (int i = 0; i < n; i ++)
      printf("%d %d\n", ans[0][i], ans[1][i]);
  }
  return 0;
}
