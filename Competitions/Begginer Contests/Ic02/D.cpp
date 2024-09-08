#include <bits/stdc++.h>
using namespace std;

struct posi
{
  int x, y;
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int Y, X, friends;
    scanf("%d %d %d\n", &Y, &X, &friends);
    int ler, bestX, bestY;
    struct posi p[friends];
    for (ler = 0; ler < friends; ler ++)
    {
      scanf("%d %d", p[ler].x, p[ler].y);
    }
    int check, dist, bestDist = 99999;
    for (ler = 0; ler < friends; ler ++)
    {
      dist = 0;
      for (check = 0; check < friends; check ++)
      {
        if (ler != check)
        {
          dist += sqrt(pow(p[ler].x - p[check].x, 2) + pow(p[ler].y - p[check].y, 2));
        }
      }
      if (dist < bestDist)
      {
        bestDist = dist;
        bestX = p[ler].x;
        bestY = p[ler].y;
      }
    }
    printf("(Street: %d, Avenue: %d)\n", bestX, bestY);
    tests --;
  }
}
