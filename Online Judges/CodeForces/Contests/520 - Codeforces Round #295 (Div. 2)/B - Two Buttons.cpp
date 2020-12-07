#include <bits/stdc++.h>
using namespace std;

int bfs(int origin, int destination)
{
  deque<pair<int, int> > queue;
  int done[1000000]; memset(done, 0, sizeof(done));
  int now = origin, steps = 0;
  queue.push_back({now, steps});
  while (1)
  {
    now = queue.front().first;
    steps = queue.front().second;
    queue.pop_front();
    if (done[now]) continue;
    done[now] = 1;
    if (now == destination) return(steps);
    if (now < destination)
      queue.push_back({now * 2, steps + 1});
    if (now > 1)
      queue.push_back({now - 1, steps + 1});
  }
}

int main()
{
  int origin, destination; scanf("%d %d", &origin, &destination);
  int answer = bfs(origin, destination);
  printf("%d\n", answer);
  return(0);
}