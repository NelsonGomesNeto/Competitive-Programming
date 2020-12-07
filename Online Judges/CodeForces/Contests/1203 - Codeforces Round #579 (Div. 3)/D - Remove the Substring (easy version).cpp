#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1], t[maxN + 1];
int sSize, tSize;
int maxRight[maxN + 1];

int main()
{
  while (scanf("%s\n%s", s, t) != EOF)
  {
    getchar();
    sSize = strlen(s), tSize = strlen(t);

    maxRight[tSize] = sSize;

    for (int i = tSize - 1; i >= 0; i --)
    {
      int pos = maxRight[i + 1] - 1;
      while (s[pos] != t[i]) pos --;
      maxRight[i] = pos;
    }

    int ans = 0;
    for (int i = 0, pos = 0; i < sSize; i ++)
    {
      ans = max(ans, (maxRight[pos] - 1) - i + 1);
      if (pos < tSize && s[i] == t[pos]) pos ++;
    }
    printf("%d\n", ans);
  }
  return(0);
}