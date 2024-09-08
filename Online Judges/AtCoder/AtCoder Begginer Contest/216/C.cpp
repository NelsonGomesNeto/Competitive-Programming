#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    string ans = "";
    while (n)
    {
      if (n & 1)
      {
        ans += "A";
        n -= 1;
      }
      if (n)
      {
        n >>= 1;
        ans += "B";
      }
    }
    reverse(ans.begin(), ans.end());
    printf("%s\n", ans.c_str());
  }
  return 0;
}