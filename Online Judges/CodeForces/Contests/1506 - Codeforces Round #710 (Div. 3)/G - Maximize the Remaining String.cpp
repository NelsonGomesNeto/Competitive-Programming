#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char ss[maxN + 1];
string s;
int cnt[256];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = string(ss);
    n = s.size();

    set<char> allLetters;
    for (int i = n - 1; i >= 0; i--)
      allLetters.insert(s[i]);
    set<char> toPut = allLetters;

    string ans = "";
    int end = 0;
    while (!toPut.empty())
    {
      set<char> curr;
      int i = n - 1;
      while (i >= end && curr != toPut)
      {
        if (toPut.count(s[i]))
          curr.insert(s[i]);
        i--;
      }
      i++;
      DEBUG printf("\tfound suffix: %d %s\n", i, s.substr(i).c_str());

      char bestLetter = '\0'; int pos = -1;
      while (i >= end)
      {
        DEBUG printf("\t\t%d %c\n", i, s[i]);
        if (s[i] >= bestLetter && toPut.count(s[i]))
        {
          bestLetter = s[i], pos = i;
          DEBUG printf("\t\t\t%c %d\n", bestLetter, pos);
        }
        i--;
      }
      ans += bestLetter;
      toPut.erase(bestLetter);
      end = pos + 1;

      DEBUG printf("\t%d - %s\n", end, ans.c_str());

      assert(bestLetter != '\0' && pos != -1);
    }

    printf("%s\n", ans.c_str());
  }
  return 0;
}
