#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    char s[53]; scanf(" %s", s);

    int cnt[256]; fill(cnt, cnt+256, 0);
    for (int i = 0; s[i]; i++) cnt[s[i]]++;

    string ans = "";
    for (int j = 0; j < 2; j++)
      for (char i = 'a'; i <= 'z'; i++)
        while (cnt[i])
          ans += i, cnt[i]--;
    printf("%s\n", ans.c_str());
  }
  return 0;
}
