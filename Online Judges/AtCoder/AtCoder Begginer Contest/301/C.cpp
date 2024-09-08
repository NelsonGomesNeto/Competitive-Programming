#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
char ss[maxN + 1];
string s, t;

vector<int> sCnt, tCnt;
set<char> allowedLetters = {'a', 't', 'c', 'o', 'd', 'e', 'r'};

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    scanf(" %s", ss);
    t = string(ss);
    DEBUG printf("\t%s %s\n", s.c_str(), t.c_str());

    sCnt.clear();
    sCnt.resize(256, 0);
    tCnt = sCnt;

    for (int i = 0; i < s.size(); ++i)
      ++sCnt[s[i]], ++tCnt[t[i]];

    int sa = sCnt['@'], ta = tCnt['@'];

    bool can = true;
    for (char l = 'a'; l <= 'z'; ++l)
    {
      int sl = sCnt[l], tl = tCnt[l];
      if (sl != tl)
      {
        if (!allowedLetters.count(l)) can = false;

        if (sl < tl) sa -= tl - sl;
        else ta -= sl - tl;
      }
    }

    printf("%s\n", can && sa == ta && ta >= 0 ? "Yes" : "No");
  }
  return 0;
}
