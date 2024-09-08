#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
char s[maxN + 1], t[maxN + 1];

int main()
{
  scanf(" %s", s);
  scanf(" %s", t);

  int n = strlen(s);

  bool can = strcmp(s, t) == 0;
  int diff = 0;
  for (int i = 0; i < n; i++)
  {
    diff += s[i] != t[i];
    if (s[i] != t[i])
    {
      if (i + 1 < n)
      {
        can = s[i + 1] != t[i + 1] && s[i] == t[i + 1] && s[i + 1] == t[i];
        diff++;
        i++;
      }
      else
        can = false;
    }
  }
  if (diff == 0 || diff == 2) can &= true;
  else can = false;
  printf("%s\n", can ? "Yes" : "No");

  return 0;
}