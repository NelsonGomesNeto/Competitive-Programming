#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
char ss[maxN + 1];

int main()
{
  while (~scanf(" %s", ss))
  {
    string s = string(ss);

    string ans = ""; int startPos = s.size();
    unordered_map<string, int> cnt;
    for (int sz = 1; sz <= s.size() && ans.empty(); sz++)
    {
      cnt.clear();
      for (int i = 0; i + sz <= s.size(); i++)
      {
        string t = s.substr(i, sz);
        if (cnt.count(t)) cnt[t] = s.size();
        else cnt[t] = i;
      }

      for (auto &p: cnt)
        if (p.second < startPos)
        {
          startPos = p.second;
          ans = p.first;
        }
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}