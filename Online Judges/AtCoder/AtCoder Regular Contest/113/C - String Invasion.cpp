#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
char ss[maxN + 1];
string s;

int acc['z' - 'a' + 1][maxN + 1];
int cnt(char target, int lo, int hi)
{
  int ans = 0;
  for (int i = lo; i <= hi; i++)
    ans += s[i] == target;
  return ans;
}
lli solve()
{
  lli ans = 0;
  int prv = s.size() - 1; char prvChar = '\0';
  for (int i = s.size() - 1; i >= 2; i--)
  {
    if (s[i - 2] == s[i - 1] && s[i - 2] != s[i])
    {
      DEBUG printf("\t%d %d %c\n", i, prv, prvChar);
      if (s[i - 2] == prvChar)
        ans += prv - i - cnt(s[i - 2], i, prv - 1);
      else
        ans += s.size() - i - cnt(s[i - 2], i, prv);
      prv = i - 2, prvChar = s[i - 2];
    }
  }
  return ans;
}

int main()
{
  
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    for (char a = 'a'; a <= 'z'; a++)
      for (int i = 0; i < s.size(); i++)
        acc[a - 'a'][i + 1] = acc[a - 'a'][i] + (s[i] == a);

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}