#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char s[4], t[4];

int main()
{
  scanf("%s\n%s", s, t);
  int ans = 0;
  for (int i = 0; s[i] && t[i]; i ++)
    ans += s[i] == t[i];
  printf("%d\n", ans);

  return(0);
}