#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    char ver[11];
    map<string, int> cnt;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ver);
      string s = string(ver);
      if (!cnt.count(s)) cnt[s] = 0;
      cnt[s]++;
    }

    vector<string> v = {"AC", "WA", "TLE", "RE"};
    for (string vv: v)
    {
      if (!cnt.count(vv))
        cnt[vv] = 0;
      printf("%s x %d\n", vv.c_str(), cnt[vv]);
    }
  }
  return 0;
}