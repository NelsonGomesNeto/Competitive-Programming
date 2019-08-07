#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int c, d, t = 1;
int dp[51];

int tryAll(char r[], int i)
{
  if (i >= c - 1) return(0);
  if (r[i] == 'X') return(99999);
  if (dp[i] == -1)
  {
    DEBUG printf("%d\n", i);
    int jumps = 99999;
    for (int j = d; j >= 1; j --)
      jumps = min(jumps, tryAll(r, i + j) + 1);
    dp[i] = jumps;
  }
  return(dp[i]);
}

int main()
{
  int tests; scanf("%d\n", &tests);
  while (scanf("%d %d", &c, &d) && t <= tests)
  {
    memset(dp, -1, sizeof(dp));
    d ++;
    char rocks[c + 1]; scanf("\n%s", rocks);
    int minimum = 99999;
    if (d == 0)
      minimum = 0;
    else
      minimum = tryAll(rocks, 0);
    if (minimum >= 99999)
      minimum = 0;
    printf("Caso #%d: %d\n", t ++, minimum);
    printf("%c\n", rocks[123023]);
  }
  return(0);
}