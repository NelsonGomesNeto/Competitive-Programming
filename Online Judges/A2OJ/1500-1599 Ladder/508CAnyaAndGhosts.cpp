#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int m, t, r; scanf("%d %d %d", &m, &t, &r);
  int ghosts[m]; for (int i = 0; i < m; i ++) scanf("%d", &ghosts[i]);

  if (r > t) printf("-1\n");
  else
  {
    bool on[601]; int t0 = 300, tf = ghosts[m - 1]; memset(on, false, sizeof(on));
    int amountOfLights[m]; memset(amountOfLights, 0, sizeof(amountOfLights));
    for (int i = 0; i < m; i ++)
    {
      for (int j = t; j >= 1; j --) if (on[t0 + ghosts[i] - j]) amountOfLights[i] ++;
      for (int j = 1; j <= r; j ++)
      {
        if (amountOfLights[i] >= r) break;
        on[t0 + ghosts[i] - j] = true, amountOfLights[i] ++;
      }
    }

    DEBUG for (int i = -t - 1; i <= tf; i ++) printf("%4d%c", i, i < tf ? ' ' : '\n');
    DEBUG for (int i = -t - 1; i <= tf; i ++) printf("%4d%c", on[i + t0] != 0, i < tf ? ' ' : '\n');

    int ans = 0;
    for (int i = 0; i < 601; i ++) ans += on[i];
    printf("%d\n", ans);
  }
  
  return(0);
}
/*
Mark every k before a ghots
*/