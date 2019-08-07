#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, int> schedule[n];
  for (int i = 0; i < n; i ++) scanf("%d %d", &schedule[i].second, &schedule[i].first);
  sort(schedule, schedule+n);

  int ended = schedule[0].first, can = 1;
  for (int i = 0; i < n; i ++)
    if (schedule[i].second >= ended)
    {
      ended = schedule[i].first;
      can ++;
    }

  printf("%d\n", can);

  return(0);
}