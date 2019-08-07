#include <bits/stdc++.h>
int relation[100][100], bestBand[3], bestRelation = -1;

void save(int band[])
{
  int actual = 0;
  for (int i = 0; i < 3; i ++)
    for (int j = i + 1; j < 3; j ++)
      actual += relation[band[i]][band[j]];
  if (actual >= bestRelation)
  {
    bestRelation = actual;
    memcpy(bestBand, band, sizeof(bestBand));
  }
}

void bruteForce(int members, int prev, int n, int band[])
{
  if (members == 3)
  {
    save(band);
    return;
  }

  for (int i = prev + 1; i < n; i ++)
  {
    band[members] = i;
    bruteForce(members + 1, i, n, band);
  }
}

int main()
{
  memset(relation, 0, sizeof(relation));

  int n, m; scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, c; scanf("%d %d %d", &u, &v, &c); u --; v --;
    relation[u][v] = c;
    relation[v][u] = c;
  }

  int band[3];
  bruteForce(0, -1, n, band);
  printf("%d %d %d\n", bestBand[0] + 1, bestBand[1] + 1, bestBand[2] + 1);

  return(0);
}