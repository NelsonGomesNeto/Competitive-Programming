#include <bits/stdc++.h>

int main()
{
  int days, timeToRead; scanf("%d %d", &days, &timeToRead);
  int worked, finished = 0;
  for (int i = 0; i < days; i ++)
  {
    scanf("%d", &worked);
    timeToRead -= (86400 - worked);
    if (timeToRead <= 0 && !finished)
      finished = i + 1;
  }

  printf("%d\n", finished);

  return(0);
}