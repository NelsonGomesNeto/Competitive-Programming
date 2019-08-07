#include <stdio.h>

int sumSquares(int n)
{
  if (n == 0) return(0);
  int d = n % 10;
  return((d * d) + sumSquares(n / 10));
}

int isHappy(int n, int backUp)
{
  int sum = sumSquares(n);
  //printf("%d\n", sum);
  if (sum == 1) return(1);
  if (sum == 4) return(0);
  return(isHappy(sum, backUp));
}

int isHappyInsaneJardel(int n, int backUp, int bug)
{
  n = sumSquares(n); bug = sumSquares(sumSquares(bug));
  if (n == 1) return(1);
  if (n == bug) return(0);
  return(isHappyInsaneJardel(n, backUp, bug));
}

int main()
{
  int n; scanf("%d", &n);
  printf("%c\n", isHappyInsaneJardel(n, n, n) ? 'S' : 'N');
  return(0);
}