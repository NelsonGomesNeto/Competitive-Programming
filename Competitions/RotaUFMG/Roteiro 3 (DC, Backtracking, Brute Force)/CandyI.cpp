#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) && n != -1)
  {
    int candy[n], sum = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &candy[i]);
      sum += candy[i];
    }

    if (!(sum % n))
    {
      int part = sum / n, moves = 0;
      sort(candy, candy+n);
      for (int j = n - 1; j >= 0 && candy[j] > part; j --)
        moves += candy[j] - part;
      printf("%d\n", moves);
    }
    else
      printf("-1\n");
  }
  return(0);
}