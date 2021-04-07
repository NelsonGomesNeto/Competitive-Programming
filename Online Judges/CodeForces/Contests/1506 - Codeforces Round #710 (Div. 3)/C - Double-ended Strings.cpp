#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20;
char ss[maxN + 1];
string a, b;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss); a = string(ss);
    scanf(" %s", ss); b = string(ss);

    int ans = 1e6;
    for (int i = 0; i < a.size(); i++)
      for (int j = a.size() - 1; j >= i - 1; j--)
        for (int p = 0; p < b.size(); p++)
          for (int m = b.size(); m >= p - 1; m--)
            if (j - i == m - p && a.substr(i, j - i + 1) == b.substr(p, m - p + 1))
            {
              ans = min(ans, (int)a.size() - (j - i + 1) + (int)b.size() - (m - p + 1));
              DEBUG
                if (j - i >= 0)
                  printf("\t%d %d | %d %d | %s %s\n", i, j, p, m, a.substr(i, j - i + 1).c_str(), b.substr(p, m - p + 1).c_str());
            }
    printf("%d\n", ans);
  }
  return 0;
}
