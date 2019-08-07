#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 20, maxSize = 40; int n[2];
char strings[2][maxN][maxSize + 1], now[2][maxSize + 1]; int sizes[2][maxN], nowSize[2], ok;

void read(int kind)
{
  for (int i = 0; i < n[kind]; i ++)
  {
    scanf(" %s", strings[kind][i]);
    sizes[kind][i] = strlen(strings[kind][i]);
  }
}

int compare() // 0 - impossible, 1 - add on 0, 2 - add on 1, 3 - match
{
  if (!nowSize[0]) return(1);
  if (!nowSize[1]) return(2);
  for (int i = ok, end = min(nowSize[0], nowSize[1]); i < end; i ++)
    if (now[0][i] != now[1][i])
      return(0);
  ok = min(nowSize[0], nowSize[1]);
  if (nowSize[0] == nowSize[1]) return(3);
  if (nowSize[0] < nowSize[1]) return(1);
  return(2);
}

void add(int kind, int i)
{
  for (int &j = nowSize[kind], a = 0; a < sizes[kind][i]; a ++, j ++)
    now[kind][j] = strings[kind][i][a];
}
bool solve()
{
  int ret = compare();
  if (ret == 0) return(false);
  if (ret == 3) return(true);
  int kind = ret - 1;
  for (int i = 0; i < n[kind]; i ++)
  {
    if (nowSize[kind] + sizes[kind][i] > maxSize) continue;
    int aux = nowSize[kind], auxok = ok;
    add(kind, i);
    if (solve()) return(true);
    nowSize[kind] = aux, ok = auxok;
  }
  return(false);
}

int main()
{
  while (scanf("%d %d", &n[0], &n[1]) != EOF)
  {
    read(0); read(1);
    memset(now, '\0', sizeof(now)), memset(nowSize, 0, sizeof(nowSize)), ok = 0;
    bool can = solve();
    printf("%c\n", can ? 'S' : 'N');
  }
  return(0);
}