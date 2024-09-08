#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char ss[maxN + 1];
string s;

bool valid(string curr)
{
  for (int i = 0; i + curr.size() - 1 < s.size(); i++)
    if (curr == s.substr(i, curr.size()))
      return false;
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", ss);
    s = string(ss);

    string ans = "a";
    while (!valid(ans))
    {
      DEBUG printf("\t%s\n", ans.c_str());
      if (ans.back() == 'z')
      {
        int i = ans.size() - 1;
        while (i >= 0 && ans[i] == 'z') ans[i--] = 'a';

        if (i < 0)
          ans += 'a';
        else
          ans[i]++;
      }
      else
        ans.back()++;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
