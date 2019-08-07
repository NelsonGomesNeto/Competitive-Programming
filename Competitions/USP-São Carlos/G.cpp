#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, int> car[n];
  for (int i = 0; i < n; i ++) scanf("%d %d", &car[i].first, &car[i].second);
  sort(car, car+n);
  double t = 0;
  for (int i = n - 1; i >= 0; i --)
  {
    int start = i; i --;
    while (i >= 0 && car[start].second < car[i].second)
    {
      t = max(t, (double) (car[start].first - car[i].first) / (car[i].second - car[start].second));
      i --;
    }
    i ++;
  }
  printf("%lf\n", t);
  return(0);
}