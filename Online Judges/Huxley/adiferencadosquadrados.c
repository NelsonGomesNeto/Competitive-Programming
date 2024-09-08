#include <stdio.h>

int main()
{
  int dp[10001][2];
  int bigSquare = 1, smallSquare = 0;
  for (bigSquare = 1, smallSquare = 0; (bigSquare * bigSquare) - (smallSquare * smallSquare) <= 10001; bigSquare ++, smallSquare ++)
  {
    long long int bigPot = bigSquare * bigSquare;
    long long int smallPot = smallSquare * smallSquare;
    dp[bigPot - smallPot][0] = bigPot;
    dp[bigPot - smallPot][1] = smallPot;
  }
  int impar;
  while (scanf("%d", &impar) && impar != 0)
    printf("%d - %d\n", dp[impar][0], dp[impar][1]);

  return(0);
}
