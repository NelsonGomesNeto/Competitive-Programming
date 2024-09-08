#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);

    bool flipped = false;
    list<char> hehe;
    for (int i = 0; i < s.size(); i++)
    {
      if (s[i] == 'R')
        flipped = !flipped;
      else
      {
        if (flipped)
        {
          if (hehe.front() == s[i]) hehe.pop_front();
          else hehe.push_front(s[i]);
        }
        else
        {
          if (hehe.back() == s[i]) hehe.pop_back();
          else hehe.push_back(s[i]);
        }
      }
    }

    string res = "";
    for (char c: hehe)
      res += c;
    if (flipped)
      reverse(res.begin(), res.end());
    DEBUG printf("\t%s\n", res.c_str());

    string ans = "";
    for (int i = 0; i < res.size(); i++)
    {
      int j = i;
      while (j + 1 < res.size() && res[i] == res[j + 1])
        j++;
      // printf("\tnow %d %d | %d | %c\n", i, j, j - i + 1, res[i]);

      if ((j - i + 1) & 1)
        ans += res[i];

      i = j;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}