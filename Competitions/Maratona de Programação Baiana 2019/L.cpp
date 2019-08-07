#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  for (int i = 0; i < 7; i ++)
  {
    int s = 0, a;
    for (int j = 0; j < 7; j ++) { scanf("%d", &a); s += a; }
    printf("%d\n", s);
  }
  return(0);
}