#include <bits/stdc++.h>
using namespace std;
int inf = 999999;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int puzzles[m], i, small = inf, big = 0;
  for (i = 0; i < m; i ++)
    scanf("%d", &puzzles[i]);

  sort(puzzles, puzzles + m);

  int best = inf;
  for (i = 0; i <= m - n; i ++)
    best = min(best, puzzles[(n + i) - 1] - puzzles[i]);

  printf("%d\n", best);

  return(0);
}