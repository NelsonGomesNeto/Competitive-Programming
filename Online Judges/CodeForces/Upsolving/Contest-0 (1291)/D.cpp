#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1; int q;
char ss[maxN];
int acc[2][maxN];
string s;

int main()
{
  int t = 0;
  while (scanf(" %s", ss) != EOF)
  {
    if (t ++) printf("\n");

    s = string(ss);
    for (int i = 0; i < s.size(); i ++)
    {
      int j = i;
      while (j + 1 < s.size() && s[i] == s[j + 1]) j ++;
      for (int k = i; k <= j; k ++)
      {
        acc[0][k + 1] = acc[0][k] + (k==i&&!((j - i + 1) & 1));
        acc[1][k + 1] = acc[1][k] + (k==i&&((j - i + 1) & 1));
      }
      i = j;
    }

    scanf("%d", &q);
    while (q --)
    {
      int l, r; scanf("%d %d", &l, &r); l --, r --;
      if (l == r) { printf("Yes\n"); continue; }

      int lol = acc[0][r + 1] - acc[0][l];
      int lol2 = acc[1][r + 1] - acc[1][l];
      DEBUG printf("%d %d | %d %d - %s\n", l, r, lol, lol2, s.substr(l, r - l + 1).c_str());
      printf("%s\n", lol + lol2 <= 1 ? "No" : "Yes");
    }
  }
  return 0;
}
