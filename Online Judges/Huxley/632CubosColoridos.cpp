#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

/*
0
1 3 4 5
2
*/

const int maxN = 1e3; int n;
int cubes[maxN][6], cubesColor[maxN][10], ans;
int read[6] = {0, 1, 3, 4, 5, 2};
int axis[3][6] = {{0, 1, 2, 4, 3, 5}, {0, 3, 2, 5, 4, 1}, {1, 3, 4, 5, 0, 2}};
bool repeated[maxN];

bool equalCubes(int i, int j)
{
  for (int k = 0; k < 10; k ++)
    if (cubesColor[i][k] != cubesColor[j][k])
      return(false);
  for (int k = 0; k < 3; k ++)
    for (int m = 0; m < 3; m ++)
      for (int start = 0; start < 4; start ++)
      {
        bool match = true;
        for (int a = 0, b = start; a < 4; a ++, b = (b + 1) % 4)
          if (cubes[i][axis[k][a]] != cubes[j][axis[m][b]])
            match = false;
        for (int a = 4; a < 6; a ++)
          if (cubes[i][axis[k][a]] != cubes[j][axis[m][a]])
            match = false;
        if (match) return(true);
      }
  return(false);
}

int main()
{
  while (scanf("%d", &n) != EOF && n)
  {
    ans = 0, memset(repeated, false, sizeof(repeated));
    memset(cubesColor, 0, sizeof(cubesColor));
    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < 6; j ++)
      {
        scanf("%d", &cubes[i][read[j]]);
        cubesColor[i][cubes[i][read[j]]] ++;
      }

      for (int j = 0; j < i; j ++)
        if (!repeated[j] && equalCubes(i, j))
        {
          repeated[i] = true;
          break;
        }
      ans += !repeated[i];
    }

    printf("%d\n", ans);
  }
  return(0);
}