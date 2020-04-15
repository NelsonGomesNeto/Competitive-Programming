#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

char s[101];
bool isPal(int ii, int jj)
{
  for (int i = ii, j = jj; i < j; i++, j--)
    if (s[i] != s[j])
      return false;
  return true;
}

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    bool ans = true; int n = strlen(s);
    ans = isPal(0, n - 1) && isPal(0, (n - 1) / 2 - 1) && isPal((n + 3) / 2 - 1, n - 1);
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}