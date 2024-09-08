#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    string ans = "";
    int before = -1;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '1')
        ans += before == 2 ? "0" : "1";
      else if (s[i] == '0')
        ans += before == 1 ? "0" : "1";
      before = (ans.back() - '0') + (s[i] - '0');
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
