#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
char ss[maxN + 1];

int main()
{
  while (scanf(" %s", ss) != EOF)
  {
    string s = string(ss);
    scanf(" %s", ss);
    string t = string(ss);

    int ans = t.size();
    for (int i = 0; i + t.size() - 1 < s.size(); i++)
    {
      int diff = 0;
      for (int j = 0; j < t.size(); j++)
        diff += t[j] != s[i + j];
      ans = min(ans, diff);
    }

    printf("%d\n", ans);
  }
  return 0;
}
