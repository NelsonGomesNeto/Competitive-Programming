#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
int number[maxN];
int f[10];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%1d", &number[i]);
  for (int i = 1; i <= 9; i ++)
    scanf("%d", &f[i]);

  for (int i = 0; i < n; i ++)
    if (f[number[i]] > number[i])
    {
      int end = i;
      while (end + 1 < n && f[number[end + 1]] >= number[end + 1]) end ++;
      for (int j = i; j <= end; j ++)
        number[j] = f[number[j]];
      break;
    }
  for (int i = 0; i < n; i ++)
    printf("%d", number[i]);
  printf("\n");

  return(0);
}