#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
char ss[maxN];
const string t = "oxx";

int main()
{
  while (~scanf(" %s", ss))
  {
    string s = string(ss);

    bool can = false;
    for (int j = 0; j < 3; j++)
    {
      bool valid = true;
      for (int i = 0; i < s.size(); i++)
        if (s[i] != t[(i + j) % 3])
          valid = false;
      if (valid) can = true;
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}