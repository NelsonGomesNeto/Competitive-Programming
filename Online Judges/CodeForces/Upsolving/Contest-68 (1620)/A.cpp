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
    char s[51]; scanf(" %s", s);
    int n = strlen(s);
    int nCnt = 0;
    for (int i = 0; i < n; i++) nCnt += s[i] == 'N';

    if (nCnt == 1)
      printf("NO\n");
    else
      printf("YES\n");
  }
  return 0;
}