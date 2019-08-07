#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int a[n], x;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &x);
    a[i] = x - 1;
  }

  int minGroup = 0;
  for (int i = 0; i < n; i ++)
  {
    int size = 1, now = i;
    while (a[now] != -2)
    {
      size ++;
      now = a[now];
    }
    minGroup = max(minGroup, size);
  }
  printf("%d\n", minGroup);

  return(0);
}