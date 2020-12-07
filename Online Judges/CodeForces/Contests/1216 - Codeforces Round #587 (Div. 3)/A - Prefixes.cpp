#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  char s[n + 1]; scanf("%s", s);
  int ans = 0, a = 0, b = 0;
  for (int i = 0; i < n; i ++)
  {
    a += s[i] == 'a', b += s[i] == 'b';
    if ((i & 1) && a != b)
    {
      if (s[i] == 'a') s[i] = 'b', a --, b ++;
      else if (s[i] == 'b') s[i] = 'a', a ++, b --;
      ans ++;
    }
  }
  printf("%d\n%s\n", ans, s);
  return(0);
}
