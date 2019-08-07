#include <bits/stdc++.h>
using namespace std;

const int maxN = 100; int n;
char s[maxN][maxN + 1], target[11] = "ICPCASIASG";
int di[8] = {-1, -1, 1, 1, -2, -2, 2, 2};
int dj[8] = {-2, 2, -2, 2, -1, 1, -1, 1};

int go(int i, int j, int p)
{
  if (i < 0 || j < 0 || i >= n || j >= n || s[i][j] != target[p]) return(false);
  if (p == 9) return(true);

  for (int k = 0; k < 8; k ++)
    if (go(i + di[k], j + dj[k], p + 1))
      return(true);
  return(false);
}

int main()
{
  scanf("%d", &n);
  char ss[n*n + 1]; scanf(" %s", ss);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      s[i][j] = ss[i*n + j];

  bool can = false;
  for (int i = 0; i < n && !can; i ++)
    for (int j = 0; j < n && !can; j ++)
      if (s[i][j] == target[0])
        can = go(i, j, 0);
  printf("%s\n", can ? "YES" : "NO");

  return(0);
}