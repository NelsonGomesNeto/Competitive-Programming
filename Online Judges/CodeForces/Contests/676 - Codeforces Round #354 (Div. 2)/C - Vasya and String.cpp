#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int f[2][(int) 1e5];

int binSearch(int lo, int hi, int at, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi - 1) return(f[at][hi] == target ? hi : f[at][lo] == target ? lo : 0);

  if (target < f[at][mid])
    return(binSearch(lo, mid - 1, at, target));
  else
    return(binSearch(mid, hi, at, target));
  return(0);
}

int main()
{
  int size, k; scanf("%d %d\n", &size, &k);
  char s[size + 1]; scanf("%s", s);
  int a = 0, b = 0;
  for (int i = 0; i < size; i ++)
  {
    if (s[i] == 'a') a ++;
    else b ++;
    f[0][i] = a;
    f[1][i] = b;
  }

  DEBUG for (int i = 0; i < size; i ++) printf("%d%c", f[0][i], i < size - 1 ? ' ' : '\n');
  DEBUG for (int i = 0; i < size; i ++) printf("%d%c", f[1][i], i < size - 1 ? ' ' : '\n');

  if (b <= k || a <= k) printf("%d\n", size);
  else
  {
    int best = 1;
    for (int j = 0; j < 2; j ++)
    {
      for (int i = size - 1; i >= 0; i --)
      {
        if (f[j][i] - k - 1 >= 0)
        {
          int pos = binSearch(0, size - 1, j, f[j][i] - k - 1);
          //printf("%d from to %d %d\n", j, pos, i);
          best = max(best, min(f[1 - j][i] - f[1 - j][pos] + k, size));
        }
        else
          best = max(best, min(f[1 - j][i] + k, size));
      }
    }
    printf("%d\n", best);
  }
  
  return(0);
}