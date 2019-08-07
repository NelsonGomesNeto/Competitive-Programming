#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m; scanf("%d %d", &n, &m);
    int letterCost[256]; for (int i = 0; i < 256; i ++) letterCost[i] = 10;
    char s[n + 1], c[n + 1]; scanf(" %s %s", s, c);
    for (int i = 0; s[i]; i ++)
      letterCost[s[i]] = min(letterCost[s[i]], c[i] - '0');

    char p[m + 1]; scanf(" %s", p);
    int minCost = 0; bool cant = false;
    for (int i = 0; p[i]; i ++) if (letterCost[p[i]] < 10) minCost += letterCost[p[i]]; else cant = true;
    if (cant) printf("-1\n");
    else printf("%d\n", minCost);
  }
  return(0);
}