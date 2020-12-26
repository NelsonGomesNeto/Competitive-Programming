#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int a, b;

int main()
{
  scanf("%d %d", &a, &b);
  int got = 1, p = 0;
  while (got < b)
    got += a - 1, p ++;
  printf("%d\n", p);

  return(0);
}