#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m;
  int t = 0;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    if (t++) printf("----------------\n");
    int mid = m / 2;
    for (int i = mid, j = 0; i > 0; i--, j++)
    {
      int spacing = 2*i;
      printf("%d %d\n", 1 + j, 1 + j + spacing);
    }
    for (int i = mid - !(m & 1), j = n / 2 + !(m & 1); i >= 0; i--, j++)
    {
      int spacing = 2*i + 1;
      printf("%d %d\n", 1 + j, 1 + j + spacing);
    }
  }
  return 0;
}