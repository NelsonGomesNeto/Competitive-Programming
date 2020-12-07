#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x;
char ss[maxN + 1];
lli diff[maxN + 1], loopdiff[maxN + 1];
string s;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %lld", &n, &x);
    scanf(" %s", ss); s = string(ss);
    for (int i = 0, ones = 0, zeros = 0; i < n; i ++)
    {
      s[i] == '0' ? zeros ++ : ones ++;
      diff[i] = zeros - ones;
    }

    int ans = x == 0;
    if (diff[n - 1] == 0)
    {
      for (int i = 0; i < n; i ++)
        if (diff[i] == x)
          ans = -1;
    }
    else
    {
      for (int i = 0; i < n; i ++)
      {
        if ((x - diff[i]) / diff[n - 1] < 0) continue;
        ans += (x - diff[i]) % diff[n - 1] == 0;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}