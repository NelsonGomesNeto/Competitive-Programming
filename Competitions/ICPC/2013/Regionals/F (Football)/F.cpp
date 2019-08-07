#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, g;
int games[maxN];

int main()
{
  while (scanf("%d %d", &n, &g) != EOF)
  {
    for (int i = 0, a, b; i < n; i ++)
    {
      scanf("%d %d", &a, &b);
      games[i] = a - b;
    }
    sort(games, games+n); reverse(games, games+n);

    int score = 0;
    for (int i = 0; i < n; i ++)
    {
      if (games[i] > 0) score += 3;
      else if (games[i] == 0 && g) score += 3, g --;
      else if (g > -games[i]) score += 3, g -= 1 - games[i];
      else if (g == -games[i]) score += 1, g -= -games[i];
    }
    printf("%d\n", score);

  }
  return(0);
}