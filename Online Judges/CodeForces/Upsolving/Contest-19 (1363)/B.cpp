#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// 00 01 10 11

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    char s[1001]; scanf(" %s", s);
    int n = strlen(s);
    int ans = strlen(s), ones = 0, zeros = 0;
    for (int i = 0; i < n; i++)
      ones += s[i] == '1', zeros += s[i] == '0';
    ans = min(zeros, ones);

    // // 00
    // int curr = 0;
    // for (int i = 0; s[i]; i++) curr += s[i] == '1';
    // ans = min(ans, curr);
    // // 11
    // curr = 0;
    // for (int i = 0; s[i]; i ++) curr += s[i] == '0';
    // ans = min(ans, curr);
    // 01
    int o = 0, z = 0;
    for (int i = 0, fliped = false; s[i]; i++)
    {
      o += s[i] == '1', z += s[i] == '0';
      // 01
      ans = min(ans, o + (zeros - z));
      // 10
      ans = min(ans, z + (ones - o));
    }

    printf("%d\n", ans);
  }
  return 0;
}
