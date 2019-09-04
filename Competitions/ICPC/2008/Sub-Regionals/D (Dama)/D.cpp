#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int inf = 1e6;
int i1, J1, i2, j2;
int dist[8][8];
int di[8] = {-1, 0, 1, -1, 1, -1, 0, 1}, dj[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

bool valid(int i, int j)
{
  return i >= 0 && i < 8 && j >= 0 && j < 8;
}

int main()
{
  while (scanf("%d %d %d %d", &i1, &J1, &i2, &j2) != EOF && !(!i1 && !J1 && !i2 && !j2))
  {
    i1 --, J1 --, i2 --, j2 --;
    for (int i = 0; i < 8; i ++)
      for (int j = 0; j < 8; j ++)
        dist[i][j] = inf;
    priority_queue<pair<int, pair<int, int>>> pq; pq.push({-(dist[i1][J1] = 0), {i1, J1}});
    while (!pq.empty())
    {
      int i = pq.top().second.first, j = pq.top().second.second, d = -pq.top().first; pq.pop();
      if (dist[i][j] < d) continue;
      for (int k = 0; k < 8; k ++)
        for (int l = 1; l <= 7; l ++)
        {
          int ni = i + di[k]*l, nj = j + dj[k]*l;
          if (valid(ni, nj) && dist[i][j] + 1 < dist[ni][nj])
            pq.push({-(dist[ni][nj] = dist[i][j] + 1), {ni, nj}});
        }
    }
    printf("%d\n", dist[i2][j2]);
  }
  return(0);
}