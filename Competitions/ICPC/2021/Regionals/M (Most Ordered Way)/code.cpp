#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 5e3; int n;
struct Task
{
  lli t, d;
  void read() { scanf("%lld %lld", &t, &d); }
};
Task tasks[maxN];

int ans[maxN], tasksPos[maxN];
lli accT[maxN + 1];
list<int> pending;

bool can()
{
  vector<pair<lli, lli>> worst;
  for (int i = 0; i < n; ++i) worst.emplace_back(tasks[i].d, tasks[i].t);
  sort(worst.begin(), worst.end());

  bool possible = true;
  lli tSum = 0;
  for (auto& w: worst)
  {
    tSum += w.second;
    if (tSum > w.first)
      possible = false;
  }
  return possible;
}

void swapWithLeftTask(int curr)
{
  int j = curr;
  ++tasksPos[ans[j - 1]], --tasksPos[ans[j]];
  swap(ans[j - 1], ans[j]);
  accT[j] = accT[j - 1] + tasks[ans[j - 1]].t;
  accT[j + 1] = accT[j] + tasks[ans[j]].t;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      tasks[i].read();

    if (!can())
    {
      printf("*\n");
      continue;
    }

    vector<pair<pair<lli, lli>, int>> orderedTasks;
    for (int i = 0; i < n; ++i)
      orderedTasks.push_back({{tasks[i].d, tasks[i].t}, i});
    sort(orderedTasks.begin(), orderedTasks.end());

    pending.clear();
    map<lli, int> minD;
    for (int i = 0; i < n; ++i)
    {
      ans[i] = orderedTasks[i].second;
      tasksPos[ans[i]] = i;
      accT[i + 1] = accT[i] + tasks[ans[i]].t;
      pending.push_back(i);
    }

    for (int pos = 0; pos < n; ++pos)
    {
      lli minDeltaDT = LONG_LONG_MAX; int smallestIndex = INT_MAX;
      for (int i = pos; i < n; ++i)
      {
        if (tasks[ans[i]].t <= minDeltaDT)
          smallestIndex = min(smallestIndex, ans[i]);
        minDeltaDT = min(minDeltaDT, tasks[ans[i]].d - accT[i + 1]);
      }

      DEBUG printf("\t%d - %lld %d\n", pos, minDeltaDT, smallestIndex + 1);
      assert(smallestIndex != INT_MAX);

      int j = tasksPos[smallestIndex];
      DEBUG printf("\t\t%d to %d from %d\n", smallestIndex + 1, pos, j);
      while (j - 1 >= pos && accT[j + 1] <= tasks[ans[j - 1]].d)
      {
        swapWithLeftTask(j);
        --j;
      }
      assert(j == pos);
    }

    for (int i = 0; i < n; ++i)
      printf("%d%c", ans[i] + 1, i + 1 < n ? ' ' : '\n');
  }
  return 0;
}