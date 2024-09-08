#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
 0 - 0
 1 - 1
 2 - 2
 3 - 3
 4 - 4
 5 - 5
 6 - 6
 7 - 7
 8 - 8
 9 - 9
10 - 
11 - 
12 - 
13 - 
14 - 
15 - 
16 - 
17 - 
18 - 
19 - 

*/

const int maxN = 4e3; int n, k; lli x;
char ss[maxN + 1];
string s;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %lld", &n, &k, &x);
    x--;
    scanf(" %s", ss);
    s = string(ss);

    if (k == 0)
    {
      string fuck = "";
      for (char c: s) if (c == 'a') fuck += c;
      printf("%s\n", fuck.c_str());
      continue;
    }

    vector<int> bases;
    for (int i = s.size() - 1; i >= 0; i--)
    {
      if (s[i] == '*')
      {
        int j = i;
        while (j - 1 >= 0 && s[j - 1] == s[i]) j--;
        DEBUG printf("\tlol %d %d %d\n", i, j, k);
        bases.push_back((i - j + 1) * k);
        i = j;
      }
    }
    lli mult = 1;
    for (lli b: bases) mult *= (b + 1);
    reverse(bases.begin(), bases.end());

    vector<lli> bsCnt;
    for (lli b: bases)
    {
      mult /= (b + 1);

      lli lo = 0, hi = b;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1;
        if (mult * mid <= x) lo = mid;
        else hi = mid - 1;
      }
      DEBUG printf("\tbases %lld %lld - %lld - %lld\n", b, mult, x, lo);

      bsCnt.push_back(lo);
      x -= mult * lo;
    }
    reverse(bsCnt.begin(), bsCnt.end());

    string ans = "";
    for (int i = s.size() - 1, b = 0; i >= 0; i--)
      if (s[i] == '*')
      {
        while (i >= 0 && s[i] == '*') i--;
        i++;
        assert(b < bsCnt.size());
        for (int j = 0; j < bsCnt[b]; j++) ans += 'b';
        b++;
      }
      else
        ans += s[i];
    reverse(ans.begin(), ans.end());
    printf("%s\n", ans.c_str());
  }
  return 0;
}
