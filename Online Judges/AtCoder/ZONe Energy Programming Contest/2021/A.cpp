#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char ss[13];
  while (~scanf(" %s", ss))
  {
    string s = string(ss);
    int ans = 0;
    for (int i = 0; i < s.size() - 3; i++)
      ans += (s.substr(i, 4) == "ZONe");
    printf("%d\n", ans);
  }

  return 0;
}