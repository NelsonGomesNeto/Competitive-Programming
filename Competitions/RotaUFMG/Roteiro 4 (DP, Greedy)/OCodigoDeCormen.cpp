#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++)
    printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] == target ? lo : -1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int size; scanf("%d", &size);
    int section[size], sum[size + 1]; sum[0] = 0;
    for (int i = 0; i < size; i ++)
    {
      scanf("%d", &section[i]);
      sum[i + 1] = sum[i] + section[i];
    }

    DEBUG printArray(sum, size + 1);
    vector<pair<int, int> > schedule;
    for (int i = 0; i <= size; i ++)
    {
      int searched = lowerBound(sum, 0, i + 1, sum[i] - 42);
      if (searched != -1)
      {
        DEBUG printf("%d %d\n", searched + 1, i);
        schedule.push_back({i, searched + 1});
      }
    }
    sort(schedule.begin(), schedule.end());
    if (!schedule.size()) printf("0\n");
    else
    {
      int total = 1, last = schedule[0].first, ss = schedule.size();
      for (int i = 0; i < ss; i ++)
        if (schedule[i].second > last)
        {
          total ++;
          last = schedule[i].first;
        }
      printf("%d\n", total);
    }
  }
  return(0);
}