#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int inf = 1<<20;

void printByte(int num)
{
  if (!num) return;
  printByte(num >> 1);
  printf("%d", (num & 1));
}

int bt(int key[], int got, int now, int i, int d, int m)
{
  if (i == d)
    return(__builtin_popcount(now) >= m ? got : inf);

  int minKidnap = bt(key, got + 1, now | key[i], i + 1, d, m);
  minKidnap = min(minKidnap, bt(key, got, now, i + 1, d, m));
  return(minKidnap);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int m, d; scanf("%d %d", &m, &d);
    int key[d]; memset(key, 0, sizeof(key));
    for (int i = 0; i < d; i ++)
    {
      int q, has; scanf("%d", &q);
      for (int j = 0; j < q; j ++)
      {
        scanf("%d", &has);
        key[i] |= (1 << has);
      }
      DEBUG printByte(key[i]); DEBUG printf("\n");
    }

    int minKidnap = bt(key, 0, 0, 0, d, m);
    if (minKidnap == inf)
      printf("Desastre!\n");
    else
      printf("%d\n", minKidnap);
  }
  return(0);
}