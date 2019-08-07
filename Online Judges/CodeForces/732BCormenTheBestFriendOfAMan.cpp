#include <bits/stdc++.h>

int main()
{
  int days, walks; scanf("%d %d", &days, &walks);
  int schedule[days], prev[days];
  for (int i = 0; i < days; i ++)
  {
    scanf("%d", &schedule[i]);
    prev[i] = schedule[i];
  }

  for (int i = 1; i < days - 1; i ++)
  {
    if (schedule[i] + schedule[i - 1] < walks)
      schedule[i] = walks - schedule[i - 1];
    if (schedule[i + 1] + schedule[i] < walks)
      schedule[i + 1] = walks - schedule[i];
  }

  for (int i = 0; i < days - 1; i ++)
    if (schedule[i] + schedule[i + 1] < walks)
      schedule[i] = walks - schedule[i + 1];

  int changed = 0;
  for (int i = 0; i < days; i ++) changed += abs(schedule[i] - prev[i]);

  printf("%d\n", changed);
  for (int i = 0; i < days; i ++)
    printf("%d%c", schedule[i], i < days - 1 ? ' ' : '\n');

  return(0);
}