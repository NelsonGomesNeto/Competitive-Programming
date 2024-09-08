#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20;
char ss[maxN + 1];
string s, t;

int main()
{
  int tests; scanf("%d", &tests);
  for (int tt = 1; tt <= tests; tt++)
  {
    scanf(" %s", ss); s = string(ss);
    scanf(" %s", ss); t = string(ss);

    if (s.size() > t.size()) swap(s, t);

    if (s != t.substr(0, s.size()))
      printf("-1\n");
    else
    {
      int l = lcm(s.size(), t.size());
      int smaller = l / s.size();
      string str = "";
      for (int i = 0; i < smaller; i++)
        str += s;

      bool can = true;
      for (int i = 0; i < str.size(); i += s.size())
        if (s != str.substr(i, s.size()))
          can = false;
      for (int i = 0; i < str.size(); i += t.size())
        if (t != str.substr(i, t.size()))
          can = false;
      printf("%s\n", can ? str.c_str() : "-1");
    }
  }
  return 0;
}
