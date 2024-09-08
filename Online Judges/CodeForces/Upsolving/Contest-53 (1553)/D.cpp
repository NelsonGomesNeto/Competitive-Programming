#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char ss[maxN + 1];
string s, t;

int main()
{
  int q; scanf("%d", &q);
  for (int tt = 1; tt <= q; tt++)
  {
    scanf(" %s", ss); s = string(ss);
    scanf(" %s", ss); t = string(ss);

    int ans = false;
    for (int i = s.size() - 1, j = t.size() - 1, debt = 0; i >= 0; i--)
    {
      if (s[i] == t[j] && debt == 0)
        j--;
      else
      {
        if (debt) debt--;
        else debt++;
      }

      if (j < 0)
      {
        ans = true;
        break;
      }
    }

    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
