#include <bits/stdc++.h>

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int array[n];
    for (int i = 0; i < n; i ++)
      scanf("%d", &array[i]);

    int sum = 0, best = array[0];
    for (int i = 0; i < n; i ++)
    {
      sum += array[i];
      if (sum > best) best = sum;
      if (sum < 0)
        sum = 0;
    }

    if (best > 0)
      printf("The maximum winning streak is %d.\n", best);
    else
      printf("Losing streak.\n");
  }
  return(0);
}