#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int serve[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &serve[i]);

  sort(serve, serve+n);

  int notDisappointed = 0, at = 0;
  for (int i = 0; i < n; i ++)
    if (at <= serve[i])
    {
      notDisappointed ++;
      at += serve[i];
    }

  printf("%d\n", notDisappointed);

  return(0);
}