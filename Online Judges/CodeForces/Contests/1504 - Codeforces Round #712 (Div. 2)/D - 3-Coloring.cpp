#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int mat[maxN][maxN];

int main()
{
  int n; scanf("%d", &n);

  queue<pair<int, int>> pos[2];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      pos[(i + j) & 1].push(make_pair(i, j));

  int b = -1, c;
  for (int k = 0, end = n*n; k < end; k++)
  {
    int a; scanf("%d", &a);
    if (b == -1)
    {
      c = a;
      b = a == 1 ? 2 : a == 2 ? 3 : 1;
    }

    int color, q;
    if (a == b)
    {
      // put c
      color = c, q = 1;
    }
    else if (a == c)
    {
      color = b, q = 0;
    }
    else
    {
      if (pos[0].size() > pos[1].size())
        color = b, q = 0;
      else
        color = c, q = 1;
    }

    if (pos[q].empty())
    {
      q = !q;
      for (color = 1; color <= 3; color++)
        if (color != b && color != c && color != a)
          break;
    }

    int i = pos[q].front().first, j = pos[q].front().second;
    pos[q].pop();
    printf("%d %d %d\n", color, i + 1, j + 1); fflush(stdout);
    mat[i][j] = color;
  }

  DEBUG {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        printf("%d", mat[i][j]);
      printf("\n");
    }
  }

  return 0;
}
