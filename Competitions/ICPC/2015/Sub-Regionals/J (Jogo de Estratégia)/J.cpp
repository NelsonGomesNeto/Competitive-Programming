#include <bits/stdc++.h>
using namespace std;

const int maxN = 500;
int players[maxN];

int main()
{
  int n, r; scanf("%d %d", &n, &r);
  for (int i = 0; i < r; i ++)
  {
    for (int j = 0, p; j < n; j ++)
    {
      scanf("%d", &p);
      players[j] += p;
    }
  }

  int winner = 0;
  for (int i = 0; i < n; i ++)
    if (players[i] >= players[winner])
      winner = i;
  printf("%d\n", winner + 1);

  return(0);
}