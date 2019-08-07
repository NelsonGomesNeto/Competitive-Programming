#include <stdio.h>
#include <string.h>

int best[4];

void save(int now[], int artists, int level[][artists])
{
  int points = 0, i, j;
  for (i = 0; i < 3; i ++)
    for (j = i + 1; j < 3; j ++)
      points += level[now[i]][now[j]];
  if (points > best[0])
  {
    best[0] = points;
    for (i = 0; i < 3; i ++)
      best[i + 1] = now[i] + 1;
  }
}

void bt(int now[], int artists, int level[][artists], int i, int j)
{
  if (i == 3)
  {
    save(now, artists, level);
    return;
  }
  if (j < artists)
  {
    int aux = now[i];
    now[i] = j;
    bt(now, artists, level, i + 1, j + 1);
    now[i] = aux;
    bt(now, artists, level, i, j + 1);
  }
}

int main()
{
  int artists, pairs;
  while (scanf("%d %d", &artists, &pairs) != EOF && !(artists == 0 && pairs == 0))
  {
    int level[artists][artists], i, j;
    memset(level, 0, sizeof(level));

    int u, v, c;
    for (i = 0; i < pairs; i ++)
    {
      scanf("%d %d %d", &u, &v, &c);
      u --; v --;
      level[u][v] = c;
      level[v][u] = c;
    }

    memset(best, -1, sizeof(best));
    int now[3];
    bt(now, artists, level, 0, 0);

    printf("%d %d %d\n", best[1], best[2], best[3]);
  }
  return(0);
}
