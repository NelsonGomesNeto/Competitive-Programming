#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    s = string(ss);
    bool ans = true;
    for (int i = 1; i < n; ++i)
      if (s[i - 1] == s[i])
        ans = false;
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
