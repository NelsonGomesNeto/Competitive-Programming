#include <bits/stdc++.h>
using namespace std;

int ans[6], nums[6] = {4, 8, 15, 16, 23, 42};
int q[4]; bool used[6];

bool valid()
{
  for (int j = 0; j < 4; j ++)
    if (ans[j] * ans[j + 1] != q[j])
      return(false);
  return(true);
}

bool solve(int i = 0)
{
  if (i == 6) return(valid());
  for (int j = 0; j < 6; j ++)
    if (!used[j])
    {
      used[j] = true;
      ans[i] = nums[j];
      if (solve(i + 1)) return(true);
      used[j] = false;
    }
  return(false);
}

int main()
{
  printf("? 1 2\n"); fflush(stdout); scanf("%d", &q[0]);
  printf("? 2 3\n"); fflush(stdout); scanf("%d", &q[1]);
  printf("? 3 4\n"); fflush(stdout); scanf("%d", &q[2]);
  printf("? 4 5\n"); fflush(stdout); scanf("%d", &q[3]);

  solve();

  printf("!");
  for (int i = 0; i < 6; i ++)
    printf(" %d", ans[i]);
  printf(" \n"); fflush(stdout);

  return(0);
}