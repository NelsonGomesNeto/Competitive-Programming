#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const int limit = 450;
int x[maxN], y[maxN];
int started[maxN];
int in[maxN], out[maxN];
int cnt[limit][limit];

int fillInOut(int delta, int start, int now, int xx, int yy)
{
  int at = start + xx, turn = 1;
  int lastClosest = -1;
  while (at < m)
  {
    if (turn)
    {
      if (at < now && abs(now - at) < abs(now - lastClosest))
        lastClosest = at;
      in[at] += delta;
      at += yy;
    }
    else
    {
      out[at] += delta;
      at += xx;
    }
    turn = !turn;
  }
  return lastClosest != -1 && lastClosest + yy >= now;
}
void fillCnt(int delta, int start, int xx, int yy)
{
  int blockSize = xx + yy;
  for (int i = 0; i < yy; i++)
    cnt[blockSize][(start + xx + i) % blockSize] += delta;
}
void addTrain(int now, int k)
{
  started[k] = now;
  if (x[k] + y[k] >= limit) fillInOut(1, now, now, x[k], y[k]);
  else fillCnt(1, now, x[k], y[k]);
}
int removeTrain(int now, int k)
{
  if (x[k] + y[k] >= limit) return fillInOut(-1, started[k], now, x[k], y[k]);
  else fillCnt(-1, started[k], x[k], y[k]);
  return 0;
}

int main()
{
  int tt = 0;
  while (~scanf("%d %d", &n, &m))
  {
    if (tt++) {
      memset(cnt, 0, sizeof(cnt)), memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
      printf("-----------\n");
    }
    for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);

    int curr = 0, running = 0;
    for (int i = 0; i < m; i++)
    {
      int op, k; scanf("%d %d", &op, &k); k--;
      if (op == 1) addTrain(i, k);
      else curr -= removeTrain(i, k);

      DEBUG printf("\t%d - %d - %d %d\n", i, curr, in[i], out[i]);

      curr += in[i];
      curr -= out[i];

      int ans = curr;
      for (int j = 1; j < limit; j++)
        ans += cnt[j][i % j];
      // ans = running - ans;

      printf("%d\n", ans);
    }
  }
  return 0;
}