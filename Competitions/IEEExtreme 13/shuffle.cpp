#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char aux[maxN], aux2[maxN], s[maxN];
int chm[256];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf(" %s", aux); n = strlen(aux);
    do
    {
      bool has[256]; memset(has, false, sizeof(has));
      for (int i = 0; i < n; i ++)
        has[s[i]] = true;

      

      if (aux[0] == aux[n - 1])
      {
        int i, j = 0, k;
        while (j + 1 < n && aux[0] == aux[j + 1]) j ++;
        for (i = j + 1, k = 0; i < n; i ++, k ++)
          s[k] = aux[i];
        for (; k < n; k ++)
          s[k] = aux[0];
        s[k] = '\0';
      }
      else memcpy(s, aux, sizeof(aux));

      DEBUG printf("%s\n", s);
      vector<char> lol = {'A', 'B', 'C', 'D'};
      memcpy(aux2, s, sizeof(s));
      int ans = n + 1;

      memcpy(s, aux2, sizeof(s));
      for (int i = 0; i < 4; i ++) chm[lol[i]] = 'A' + i;
      // chm['A'] = chm['B'] = chm['C'] = chm['D'] = -1;
      // for (int i = 0, at = 'A'; i < n; i ++)
      //   if (chm[s[i]] == -1)
      //     chm[s[i]] = at ++;
      for (int i = 0; i < n; i ++)
      {
        char v = chm[s[i]];
        s[i] = aux[i] = v;
      }
      sort(aux, aux+n);
      int now = 0;
      for (int i = 0; i < n; i ++)
        now += s[i] != aux[i];
      ans = min(ans, now);
      DEBUG printf("%s -- %c %c %c %c -- %d\n", s, lol[0], lol[1], lol[2], lol[3], now);
    }
    while (next_permutation(lol.begin(), lol.end()));
    printf("%d\n", ans);
  }
  return 0;
}