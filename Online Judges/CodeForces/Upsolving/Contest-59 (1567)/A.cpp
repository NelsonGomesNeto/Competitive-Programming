#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
char s[maxN + 1];
string ans;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    ans = "";
    for (int i = 0; i < n; i++)
      if (s[i] == 'U' || s[i] == 'D')
      {
        ans += s[i] == 'U' ? "D" : "U";
      }
      else
        ans += "LR", i++;
    printf("%s\n", ans.c_str());
  }
  return 0;
}
