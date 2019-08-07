#include <bits/stdc++.h>
using namespace std;

int main()
{
  char op[3];
  int lo = 1, hi = 1e6;
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    printf("%d\n", mid); fflush(stdout);
    scanf("%s", op);
    if (!strcmp(op, ">=")) lo = mid;
    else hi = mid - 1;
  }
  printf("! %d\n", lo); fflush(stdout);
  return(0);
}