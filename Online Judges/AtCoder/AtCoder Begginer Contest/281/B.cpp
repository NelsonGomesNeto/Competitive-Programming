#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool isUpperCase(char a)
{
  return a >= 'A' && a <= 'Z';
}
bool inNumRange(string s)
{
  for (char c : s)
    if (!(c >= '0' && c <= '9'))
      return false;
  return s[0] >= '1';
}


const int maxN = 10;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    bool yes = isUpperCase(s[0]) && isUpperCase(s.back())
              && s.size() == 8 && inNumRange(s.substr(1, 6));
    printf("%s\n", yes ? "Yes" : "No");
  }
  return 0;
}
