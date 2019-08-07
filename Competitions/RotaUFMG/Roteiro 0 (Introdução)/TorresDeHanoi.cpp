#include <bits/stdc++.h>
#define DEBUG if(0)
int dp[31];

int hanoi(int n, int origin, int destination, int temporary)
{
  int moves = 0;
  if (n == 1)
    moves ++;
  else
  {
    moves += hanoi(n - 1, origin, temporary, destination);
    moves ++;
    moves += hanoi(n - 1, temporary, destination, origin);
  }
  return(moves);
}

int main()
{
  DEBUG for (int i = 1; i <= 30; i ++)
  {
    dp[i] = hanoi(i, 0, 1, 2);
    printf("%d %d\n", i, dp[i]);
  }

  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t) printf("\n");

    printf("Teste %d\n%d\n", ++ t, (int) pow(2, n) - 1);
  }
  return(0);
}