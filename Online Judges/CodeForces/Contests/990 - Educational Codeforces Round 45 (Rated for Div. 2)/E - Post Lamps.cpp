#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int inf = 1<<20, n, m, k;

void read(int a[], int size)
{
  for (int i = 0; i < size; i ++) scanf("%d", &a[i]);
}

int cmp(const pair<double, int> a, const pair<double, int> b)
{
  if (a.first < b.first) return(1);
  if (a.first == b.first) return(a.second > b.second);
  return(0);
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  int b[m], a[k]; read(b, m); read(a, k);
  int blocked[n]; memset(blocked, 0, sizeof(blocked));
  for (int i = 0; i < m; i ++) blocked[b[i]] = 1;
  pair<double, int> bestLamp[k];
  for (int i = 0; i < k; i ++) bestLamp[i] = {(double) a[i] / (i + 1), i};
  sort(bestLamp, bestLamp+k, cmp);
  DEBUG for (int i = 0; i < k; i ++)
    printf("(%d, %d) [%lf]\n", bestLamp[i].second + 1, a[bestLamp[i].second], bestLamp[i].first);

  int at = 0, cost = 0;
  while (at < n)
  {
    DEBUG printf("%d\n", at);
    if (blocked[at]) break;
    int i = 0;
    while (i < k && at + bestLamp[i].second + 1 < n && blocked[at + bestLamp[i].second + 1])  i ++;
    if (i >= k) break;

    if (at + bestLamp[i].second + 1 >= n)
    {
      int best = 1<<20, bi = -1;
      while (i < k && at + bestLamp[i].second + 1 >= n)
      {
        if (a[bestLamp[i].second] < best)
        {
          best = a[bestLamp[i].second];
          bi = i;
        }
        i ++;
      }
      i = bi;
    }
    cost += a[bestLamp[i].second];
    at += bestLamp[i].second + 1;
  }
  if (at < n) printf("-1\n");
  else printf("%d\n", cost);
  
  return(0);
}