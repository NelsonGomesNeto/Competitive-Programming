#include <bits/stdc++.h>

void printSpaces(int amount)
{
  for (int i = 0; i < amount; i ++) printf(" ");
}

int main()
{
  int n; scanf("%d", &n);
  int at = 0;
  for (int i = 0; i <= 2*n; i ++)
  {
    printSpaces(2*(n - at));
    for (int j = 0; j < at; j ++) printf("%d ", j);
    printf("%d", at);
    for (int j = at - 1; j >= 0; j --) printf(" %d", j);
    // printSpaces(2*(n - at) - 1);
    printf("\n");

    if (i >= n) at --;
    else at ++;
  }
  return(0);
}