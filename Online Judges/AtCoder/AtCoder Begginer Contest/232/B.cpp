#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char ss[maxN + 1];
string s, t;
int readString(string &str)
{
  int res = scanf(" %s", ss);
  str = string(ss);
  return res;
}

int main()
{
  while (~readString(s))
  {
    readString(t);

    bool can = false;
    for (int i = 0; i < 26; i++)
    {
      bool valid = true;
      for (int j = 0; j < s.size(); j++)
        if (((s[j] - 'a') + i) % 26 + 'a' != t[j])
          valid = false;
      can |= valid;
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}