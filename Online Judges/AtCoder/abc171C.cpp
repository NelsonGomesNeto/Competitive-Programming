#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n;
  while (scanf("%lld", &n) != EOF)
  {
    n -= 1;
    lli sz = 1, at = 0, pot = 26;
    while (n - pot >= 0)
    {
      n -= pot;
      at += pot;
      pot *= 26;
      sz++;
    }
    string ans;
    for (int i = 0; i < sz; i++)
    {
      ans += (n % 26) + 'a';
      n /= 26;
    }
    reverse(ans.begin(), ans.end());
    DEBUG printf("\t%lld %lld\n", sz, n);
    printf("%s\n", ans.c_str());
  }
  return 0;
}