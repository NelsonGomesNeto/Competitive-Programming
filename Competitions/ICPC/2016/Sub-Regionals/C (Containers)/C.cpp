#include <bits/stdc++.h>
using namespace std;
#define container vector<vector<int> >
container original, destination, aux;
int inf = 1 << 20;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

template <typename General>
struct hash_function {
  size_t operator()(General const& c) const {
    size_t hashValue = 0;
    for (auto i: c) hashValue += hash<string>() (string(i.begin(), i.end()));
    return(hashValue);
  }
};
unordered_map<container, int, hash_function<container> > done;

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int valid(int i, int end)
{
  return(!(i < 0 || i >= end));
}

void printMat(container cont)
{
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < 4; j ++)
      printf("%d%c", cont[i][j], j < 4 - 1 ? ' ' : '\n');
}

int dijkstra()
{
  priority_queue<pair<int, container>, vector<pair<int, container> >, greater<pair<int, container> > > pq;
  pq.push({0, original});
  while (!pq.empty())
  {
    int c = pq.top().first; container now = pq.top().second; pq.pop();
    int someDiffer = 0;
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < 4; j ++)
        if (now[i][j] != destination[i][j])
          for (int k = 0; k < 4; k ++)
            if (valid(i + dy[k], 2) && valid(j + dx[k], 4))
            {
              someDiffer = 1;
              int cost = now[i][j] + now[i + dy[k]][j + dx[k]];
              swap(&now[i][j], &now[i + dy[k]][j + dx[k]]);
              if (!done.count(now) || done[now] > cost + c)
              {
                done[now] = cost + c;
                pq.push({cost + c, now});
              }
              swap(&now[i][j], &now[i + dy[k]][j + dx[k]]);
            }
    if (!someDiffer) return(c);
  }
}

void readContainer(container &c)
{
  for (int i = 0; i < 2; i ++)
  {
    c.push_back(vector<int>(4));
    for (int j = 0; j < 4; j ++) scanf("%d", &c[i][j]);
  }
}

int main()
{
  readContainer(original); readContainer(destination);
  int ans = dijkstra();
  printf("%d\n", ans);
  return(0);
}