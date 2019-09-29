#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    for (int j = 0; j < n; j ++) printf("%c", (i & 1 ? !(j & 1) : (j & 1)) ? 'B' : 'W');
    printf("\n");
  }
  return(0);
}
