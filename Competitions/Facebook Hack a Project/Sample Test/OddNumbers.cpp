#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int l, r; scanf("%d %d", &l, &r);
  for (int i = l; i <= r; i ++)
    if (i & 1)
      printf("%d\n", i);
  return(0);
}