#include <bits/stdc++.h>
using namespace std;
int mat[1000][1000];

vector<int> kadane(int y, int x)
{
  int best = mat[0][0], now, in = 0, jn = 0, is, js, ie, je, temp[x];
  for (int i = 0; i < y; i ++)
  {
    memset(temp, 0, sizeof(temp));
    for (int j = i; j < y; j ++)
    {
      for (int m = 0; m < x; m ++) temp[m] += mat[j][m];
      now = 0;
      for (int m = 0; m < x; m ++)
      {
        now += temp[m];
        if (now > best)
        {
          best = now;
          is = in; js = jn; ie = j; je = m;
        }
        if (now < 0)
        {
          in = i; jn = m + 1;
          now = 0;
        }
      }
    }
  }
  vector<int> ans = {is, js, ie, je, best};
  return(ans);
}

int main()
{
  int y, x, t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &y, &x);
    for (int i = 0; i < y; i ++)
    for (int j = 0; j < x; j ++)
    scanf("%d", &mat[i][j]);

    vector<int> ans = kadane(y, x);
    //printf("[%d, %d] - [%d, %d] = %d\n", ans[0], ans[1], ans[2], ans[3], ans[4]);
    printf("%d\n", ans[4]);
  }
  return(0);
}