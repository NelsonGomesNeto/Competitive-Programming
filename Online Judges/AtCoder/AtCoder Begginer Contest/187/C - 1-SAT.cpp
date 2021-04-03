#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
set<string> a, b;
string s[maxN];
char ss[11];

int main()
{
  while (~scanf("%d", &n))
  {
    a.clear(), b.clear();
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      s[i] = string(ss);
      if (s[i][0] == '!') b.insert(s[i].substr(1));
      else a.insert(s[i]);
    }

    string ans = "satisfiable";
    for (string aa: a)
      if (b.count(aa))
        ans = aa;
    printf("%s\n", ans.c_str());
  }
  return 0;
}