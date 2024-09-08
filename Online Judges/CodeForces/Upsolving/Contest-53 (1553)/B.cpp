#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n;
char ss[maxN + 1];
string s, t;

int main()
{
  int q; scanf("%d", &q);
  for (int tt = 1; tt <= q; tt++)
  {
    scanf(" %s", ss); s = string(ss);
    scanf(" %s", ss); t = string(ss);

    bool can = false;
    for (int i = 0; i < s.size() && !can; i++)
      if (s[i] == t[0])
        for (int j = 0; j < t.size() && i + j < s.size() && s[i + j] == t[j]; j++)
        {
          int rem = t.size() - j - 1;
          if (rem == 0) can = true;
          else if (i + j - rem >= 0)
          {
            string r = s.substr(i + j - rem, rem);
            reverse(r.begin(), r.end());
            string target = t.substr(j + 1, rem);
            DEBUG printf("%d %d - %s %s\n", i, j, r.c_str(), target.c_str());
            if (r == target)
              can = true;
          }
        }
    printf("%s\n", can? "YES" : "NO");
  }
  return 0;
}
