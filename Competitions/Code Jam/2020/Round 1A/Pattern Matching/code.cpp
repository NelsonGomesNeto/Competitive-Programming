#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50, maxLen = 101; int n;
const int inf = 1e4;
char ss[maxLen];
vector<string> pre, pos;
string ans;

bool check(vector<string> &strings, bool start = true)
{
  string base = "";
  for (int i = 0; i < strings.size(); i++)
    if (strings[i].size() > base.size())
      base = strings[i];
  for (int i = 0; i < base.size(); i++)
    for (int j = 0; j < strings.size(); j++)
      if (i < strings[j].size() && strings[j][i] != base[i])
        return false;
  if (start) ans = base + ans;
  else
  {
    reverse(base.begin(), base.end());
    ans = ans + base;
  }
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    ans = "", pre.clear(), pos.clear();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      string sss = string(ss);

      int hi = sss.size() - 1;
      if (sss[hi] != '*')
      {
        string lol = "";
        while (hi >= 0 && sss[hi] != '*') lol += sss[hi--];
        pos.push_back(lol);
      }
      int lo = 0;
      if (sss[lo] != '*')
      {
        string lol = "";
        while (lo < sss.size() && sss[lo] != '*') lol += sss[lo++];
        pre.push_back(lol);
      }
      for (int i = lo; i <= hi; i++)
        if (sss[i] == '*')
        {
          int j = i;
          while (j + 1 < hi && sss[j + 1] == '*') j++;
          ans += sss.substr(lo, i - lo);
          lo = j + 1;
          i = j;
        }
    }

    bool valid = check(pre, true) && check(pos, false);
    if (!valid) ans = "*";
    printf("Case #%d: %s\n", tt, ans.c_str());
  }
  return 0;
}