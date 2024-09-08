#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxS = 50;
int n;
char ss[maxS + 1];
string s[maxN];

bool isPalindrome(const string a)
{
  for (int i = 0, j = a.size() - 1; i < j; ++i, --j)
    if (a[i] != a[j])
      return false;
  return true;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      s[i] = string(ss);
    }

    bool ans = false;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
      {
        if (i == j) continue;
        ans |= isPalindrome(s[i] + s[j]);
      }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
