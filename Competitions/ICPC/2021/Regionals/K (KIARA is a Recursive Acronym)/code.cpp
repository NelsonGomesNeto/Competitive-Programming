#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
char s[maxN + 1];
string words[maxN];
bool has[256];

int main()
{
  while (~scanf("%d", &n))
  {
    memset(has, 0, sizeof(has));
    for (int i = 0; i < n; ++i)
    {
      scanf("%s", s);
      words[i] = string(s);
      has[words[i][0]] = true;
    }

    bool can = false;
    for (int i = 0; i < n; ++i)
    {
      bool possible = true;
      for (char c: words[i])
        if (!has[c])
        {
          possible = false;
          break;
        }
      can |= possible;
    }
    printf("%s\n", can ? "Y" : "N");
  }
  return 0;
}