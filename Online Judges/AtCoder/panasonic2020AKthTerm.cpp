#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int ks[32] = {1, 1, 1, 2, 1, 2, 1, 5, 2, 2, 1, 5, 1, 2, 1, 14, 1, 5, 1, 5, 2, 2, 1, 15, 2, 2, 5, 4, 1, 4, 1, 51};

int main()
{
  int k;
  while (scanf("%d", &k) != EOF)
    printf("%d\n", ks[k - 1]);
  return 0;
}