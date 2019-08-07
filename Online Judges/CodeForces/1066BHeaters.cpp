#include <bits/stdc++.h>
int n, range;

void printArray(int a[], int n)
{
  for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
}

void mark(int fire[], int start)
{
  for (int i = start + 1, r = range - 1; r && i < n; i ++, r --) fire[i] = 1;
  for (int i = start - 1, r = range - 1; r && i >= 0; i --, r --) fire[i] = 1;
}

int main()
{
  scanf("%d %d", &n, &range);
  int warmer[n], on[n], totalOn = 0; memset(on, 0, sizeof(on));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &warmer[i]);
    if (warmer[i]) totalOn ++, on[i] = 1;
  }

  int fire[n]; memset(fire, 0, sizeof(fire));
  for (int i = 0; i < n; i ++)
  {
    if (fire[i] && on[i]) totalOn --;
    else if (on[i]) mark(fire, i), fire[i] = 1;
  }

  for (int i = 0; i < n; i ++)
    if (!fire[i])
    {
      int done = 0;
      for (int j = i + 1, r = range - 1; r && j < n; j ++, r --)
        if (on[j])
        {
          mark(fire, j); totalOn ++;
          done = 1;
          break;
        }
      if (done) continue;
      for (int j = i - 1, r = range - 1; r && j >= 0; j --, r --)
        if (on[j])
        {
          mark(fire, j); totalOn ++;
          break;
        }
    }

  int can = 1;
  for (int i = 0; i < n; i ++) if (!fire[i]) can = 0;

  printf("%d\n", can ? totalOn : -1);

  return(0);
}