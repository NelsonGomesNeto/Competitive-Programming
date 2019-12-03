#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
set<string> pre, suf;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    pre.clear(), suf.clear();
    suf.insert("");

    char s[11], ans[11] = "ok";
    bool found = false;
    for (int j = 0; j < n; j ++)
    {
      scanf(" %s", s);
      string ss(s);
      for (int i = 0; i < 10 && !found; i ++)
      {
        DEBUG printf("searching: %s %s\n", ss.substr(0, i + 1).c_str(), ss.substr(i + 1, 10 - i - 1).c_str());
        if (pre.count(ss.substr(0, i + 1)) && suf.count(ss.substr(i + 1, 10 - i - 1)))
          strcpy(ans, s), found = true;
      }
      for (int i = 0; i < 10; i ++)
      {
        DEBUG printf("inserting: %s %s\n", ss.substr(0, i + 1).c_str(), ss.substr(10 - i - 1, i + 1).c_str());
        suf.insert(ss.substr(0, i + 1)), pre.insert(ss.substr(10 - i - 1, i + 1));
      }
    }
    printf("%s\n", ans);
  }
  return 0;
}