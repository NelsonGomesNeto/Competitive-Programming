#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n;
char ss[maxN + 1];
string s, t;

int main()
{
  int q; scanf("%d", &q);
  for (int tt = 1; tt <= q; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", ss);
    s = string(ss), t = string(ss);

    sort(t.begin(), t.end());

    int ans = 0;
    for (int i = 0; i < n; i++)
      ans += s[i] != t[i];
    printf("%d\n", ans);
  }
  return 0;
}