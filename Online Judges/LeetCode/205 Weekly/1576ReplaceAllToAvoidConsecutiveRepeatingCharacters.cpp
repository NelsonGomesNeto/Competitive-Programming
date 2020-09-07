#include <bits/stcd++.h>
using namespace std;

class Solution
{
public:
  string modifyString(string s)
  {
    for (int i = 0; i < s.size(); i++)
      if (s[i] == '?')
      {
        char prv = i ? s[i - 1] : '\0';
        char nxt = i + 1 < s.size() ? s[i + 1] : '\0';
        for (char a = 'a'; a <= 'z'; a++)
          if (a != prv && a != nxt)
            s[i] = a;
      }
    return s;
  }
};