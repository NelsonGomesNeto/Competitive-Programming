#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6, maxD = 19;

bool has[maxN + 1];
int qq[120];
vector<int> ans[maxN + 1][maxD];

void precalc(const int limit)
{
  for (int x = 3; x <= limit; x++)
    ans[x][1].push_back(x);

  for (int x = 3; x <= limit; x++)
  {
    // for (int s = maxD - 1; s >= 1; s--)
    for (int s = 1; s < maxD; s++)
    {
      for (int prv: ans[x][s])
      {
        for (int j = 2*prv; x + j <= limit; j += prv)
        {
          auto &curr = ans[x + j][s + 1];
          if (2*j <= limit || has[x + j])
          {
            if (curr.size() >= 12)
            {
              auto biggest = max_element(curr.begin(), curr.end());
              if (*biggest > j) *biggest = j;
            }
            else if (2*j <= limit || has[x + j])
              curr.push_back(j);
          }
        }
      }
    }
  }
}

int main()
{

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    qq[tt] = n;
    has[n] = true;
  }

  precalc(*max_element(qq+1, qq+t+1));

  for (int tt = 1; tt <= t; tt++)
  {
    int n = qq[tt];

    int res = 0;
    for (int s = 0; s < maxD; s++)
      if (!ans[n][s].empty())
        res = max(res, s);
    printf("Case #%d: %d\n", tt, res);
  }

  return 0;
}