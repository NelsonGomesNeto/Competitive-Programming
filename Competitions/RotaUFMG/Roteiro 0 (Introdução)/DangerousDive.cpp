#include <bits/stdc++.h>

int main()
{
  int n, r;
  while (scanf("%d %d", &n, &r) != EOF)
  {
    int mergulhadores[n], ret, b = r; memset(mergulhadores, 1, sizeof(mergulhadores));
    while (r -- > 0)
    {
      scanf("%d", &ret);
      mergulhadores[ret - 1] = 0;
    }

    for (int i = 0; i < n; i ++)
      if (mergulhadores[i])
        printf("%d ", i + 1);

    if (n == b)
      printf("*");

    printf("\n");
  }
  return(0);
}