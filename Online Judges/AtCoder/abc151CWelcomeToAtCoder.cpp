#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
bool solved[maxN];
int penalties[maxN];
pair<int, string> submissions[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(solved, false, sizeof(solved));
    memset(penalties, 0, sizeof(penalties));
    for (int i = 0; i < m; i ++)
    {
      int p; char s[3]; scanf("%d %s", &p, s); p --;
      submissions[i] = {p, string(s)};
    }

    int totalSolved = 0, totalPenalties = 0;
    for (int i = 0; i < m; i ++)
      if (!solved[submissions[i].first])
      {
        if (submissions[i].second == "WA")
          penalties[submissions[i].first] ++;
        else
          totalSolved ++, totalPenalties += penalties[submissions[i].first], solved[submissions[i].first] = true;
      }
    printf("%d %d\n", totalSolved, totalPenalties);
  }
  return 0;
}