#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101;
char t[maxN];

int main()
{
  int tt; scanf("%d", &tt);
  while (tt--)
  {
    scanf(" %s", t);
    int ones = 0, zeroes = 0;
    for (int i = 0; t[i]; i++)
    {
      ones += t[i] == '1';
      zeroes += t[i] == '0';
    }
    string ans;
    if (ones == 0 || zeroes == 0)
      ans = string(t);
    else
    {
      string base = t[0] == '1' ? "10" : "01";
      for (int i = 0; t[i]; i++)
        ans += base;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
