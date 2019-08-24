#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 1e5 + 1; int sSize, tSize;
char s[maxN], t[maxN];
int letterCnt[26][maxN];
int required[26];
 
int main()
{
  while (scanf("%s %s", s, t) != EOF)
  {
    // printf("%s || %s\n", s, t);
    getchar();
    memset(letterCnt, 0, sizeof(letterCnt)), memset(required, 0, sizeof(required));
    sSize = strlen(s), tSize = strlen(t);
 
    for (int i = 0; i < sSize; i ++)
    {
      if (i) for (int j = 0; j < 26; j ++) letterCnt[j][i] = letterCnt[j][i - 1];
      letterCnt[s[i] - 'a'][i] ++;
    }
    for (int i = 0; i < tSize; i ++) required[t[i] - 'a'] ++;
 
    bool can = true;
    for (int i = 0; i < 26; i ++)
      if (required[i] && !letterCnt[i][sSize - 1])
        can = false;
    if (!can) printf("-1\n");
    else
    {
      lli ans = 0; int at = 0;
      for (int i = 0; i < tSize; i ++)
      {
        int target = at == 0 ? 1 : letterCnt[t[i] - 'a'][at - 1] + 1;
        int pos = lower_bound(letterCnt[t[i] - 'a']+at, letterCnt[t[i] - 'a']+sSize, target) - letterCnt[t[i] - 'a'];
        if (pos == sSize)
        {
          ans += (sSize - at); at = 0;
          pos = lower_bound(letterCnt[t[i] - 'a']+at, letterCnt[t[i] - 'a']+sSize, 1) - letterCnt[t[i] - 'a'];
        }
        ans += (pos - at + 1); at = pos + 1;
        if (pos == sSize) ans ++, at = 0;
      }
      printf("%lld\n", ans);
    }
  }
 
  return(0);
}