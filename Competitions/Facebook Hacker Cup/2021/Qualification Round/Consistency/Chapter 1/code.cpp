#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
char s[maxN + 1];
int cnt[256];
bool isVowel(char c)
{
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    n = strlen(s);

    memset(cnt, 0, sizeof(cnt));
    int v = 0, c = 0;
    for (int i = 0; i < n; i++)
    {
      v += isVowel(s[i]), c += !isVowel(s[i]);
      cnt[s[i]]++;
    }

    int ans = 1e9;
    for (int i = 'A'; i <= 'Z'; i++)
      if (isVowel(i))
        ans = min(ans, 2*(v - cnt[i]) + c);
      else
        ans = min(ans, 2*(c - cnt[i]) + v);

    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}