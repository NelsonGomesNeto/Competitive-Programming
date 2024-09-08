#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int done[(int) 1e5 + 1];
int fat[10];

int fillFatorial()
{
  for (int i = 1, j = 2; j <= 10; i *= j, j ++)
  {
    fat[j - 1] = i;
    DEBUG printf("%d\n", fat[j - 1]);
  }
}

int bfs(int target)
{
  deque<pair<int, int> > queue;
  queue.push_back({0, 0});

  while (!queue.empty())
  {
    int now = queue.front().first, steps = queue.front().second; queue.pop_front();
    DEBUG printf("%d %d\n", now, steps);
    if (now == target) return(steps);

    if (done[now]) continue;
    done[now] = 1;
    for (int i = 1; i < 10; i ++)
      if (now + fat[i] <= target)
        queue.push_back({now + fat[i], steps + 1});
  }
  return(0);
}

int main()
{
  memset(done, 0, sizeof(done));
  fillFatorial();
  int num; scanf("%d", &num);

  int ans = bfs(num);

  printf("%d\n", ans);

  return(0);
}