#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, int> schedule[n];
  for (int i = 0; i < n; i ++)
    scanf("%d %d", &schedule[i].second, &schedule[i].first);
  sort(schedule, schedule+n);

  int total = 1, at = schedule[0].first;
  for (int i = 1; i < n; i ++)
    if (schedule[i].second >= at)
    {
      at = schedule[i].first;
      total ++;
    }

  printf("%d\n", total);
  return(0);
}