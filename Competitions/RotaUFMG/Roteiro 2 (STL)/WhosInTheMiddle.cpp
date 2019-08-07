#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int median, a[n], milk = 0;
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  sort(a, a+n);

  for (int i = 0; i < n; i ++)
    if (n & 1 && i == n / 2)
      median = a[i];
    else if (!(n & 1) && (i == n / 2 || i == n / 2 + 1))
      median += a[i];
  if (!(n & 1)) median /= 2;

  printf("%d\n", median);
  return(0);
}