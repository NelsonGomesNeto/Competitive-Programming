#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  bool finite = true;
  int points = 0;
  for (int i = 0; i < n - 1; i ++)
  {
    if ((a[i] == 2 && (a[i + 1] == 2 || a[i + 1] == 3)) || (a[i] == 3 && (a[i + 1] == 3 || a[i + 1] == 2)) || (a[i] == 1 && a[i + 1] == 1))
      finite = false;
    if ((a[i] == 1 && a[i + 1] == 2) || (a[i] == 2 && a[i + 1] == 1))
      points += 3;
    if ((a[i] == 1 && a[i + 1] == 3) || (a[i] == 3 && a[i + 1] == 1))
      points += 4;
    if (i && (a[i - 1] == 3 && a[i] == 1 && a[i + 1] == 2))
      points --;
    if (i && (a[i - 1] == 1 && a[i] == 3 && a[i + 1] == 2))
      points -= 2;
  }
  if (!finite) printf("Infinite\n");
  else printf("Finite\n%d\n", points);
  return(0);
}
