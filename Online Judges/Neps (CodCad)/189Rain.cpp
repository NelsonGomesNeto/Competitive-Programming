#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int height[n + 2], left[n + 2], right[n + 2];
  for (int i = 1; i <= n; i ++)
    scanf("%d", &height[i]);

  left[0] = left[n + 1] = 0;
  for (int i = 1; i <= n; i ++)
    left[i] = max(left[i - 1], height[i]);
  right[0] = right[n + 1] = 0;
  for (int i = n; i > 0; i --)
    right[i] = max(right[i + 1], height[i]);

  DEBUG for (int i = 0; i <= n; i ++)
    printf("%d%c", left[i], i <= n - 1 ? ' ' : '\n');
  DEBUG for (int i = 0; i <= n; i ++)
    printf("%d%c", right[i], i <= n - 1 ? ' ' : '\n');

  int water = 0;
  for (int i = 1; i <= n; i ++)
  {
    DEBUG printf("%d %d %d %d\n", height[i], left[i - 1], right[i + 1], min(left[i - 1], right[i + 1]));
    if (height[i] < min(left[i - 1], right[i + 1]))
      water ++;
  }

  printf("%d\n", water);

  return(0);
}