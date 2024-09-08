#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n, m;
char ss[maxN][maxN + 1];
string s[4*maxN];

void makeUnique(vector<int> &a)
{
  a.resize(distance(a.begin(), unique(a.begin(), a.end())));
}

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
void floodFill(int i = 0, int j = 0)
{
  if (i < 0 || j < 0 || i >= n || j >= m || s[i][j] != '.') return;

  s[i][j] = 'o';
  for (int k = 0; k < 4; k++)
    floodFill(i + di[k], j + dj[k]);
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", ss[i]);

    for (int i = 0; i < 2*n; i++)
    {
      s[i].clear();
      for (int j = 0; j < 2*m; j++)
        s[i] += ss[i >> 1][j >> 1];
        // s[i] += ss[i][j];
    }
    n*=2, m*=2;

    floodFill();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[i][j] == '.')
          s[i][j] = '#';
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[i][j] == 'o')
          s[i][j] = '.';

    DEBUG
      for (int i = 0; i < n; i++)
        printf("%s\n", s[i].c_str());

    // // count .# and #.
    // int ans = 0;
    // for (int j = 0; j < m; j++)
    //   for (int i = 0; i < n; i++)
    //   {
    //     if (j + 1 < m && s[i][j] == '.' && s[i][j + 1] == '#')
    //     {
    //       int ii = i;
    //       while (ii + 1 < n && j + 1 < m && s[ii + 1][j] == '.' && s[ii + 1][j + 1] == '#') ii++;
    //       i = ii;
    //       ans++;
    //     }
    //     if (j + 1 < m && s[i][j] == '#' && s[i][j + 1] == '.')
    //     {
    //       int ii = i;
    //       while (ii + 1 < n && j + 1 < m && s[ii + 1][j] == '#' && s[ii + 1][j + 1] == '.') ii++;
    //       i = ii;
    //       ans++;
    //     }
    //   }
  
    // for (int i = 0; i < n; i++)
    //   for (int j = 0; j < m; j++)
    //   {
    //     if (i + 1 < n && s[i][j] == '.' && s[i + 1][j] == '#')
    //     {
    //       int jj = j;
    //       while (jj + 1 < n && i + 1 < n && s[i][jj + 1] == '.' && s[i + 1][jj + 1] == '#') jj++;
    //       j = jj;
    //       ans++;
    //     }
    //     if (i + 1 < n && s[i][j] == '#' && s[i + 1][j] == '.')
    //     {
    //       int jj = j;
    //       while (jj + 1 < n && i + 1 < n && s[i][jj + 1] == '#' && s[i + 1][jj + 1] == '.') jj++;
    //       j = jj;
    //       ans++;
    //     }
    //   }

    int ans = 0;
    for (int i = 0; i + 1 < n; i++)
      for (int j = 0; j + 1 < m; j++)
      {
        char aa = '.', bb = '#';
        if (s[i][j] == aa && s[i][j + 1] == aa
         && s[i + 1][j] == aa && s[i + 1][j + 1] == bb)
        {
          ans++;
          continue;
        }

        if (s[i][j] == aa && s[i][j + 1] == aa
         && s[i + 1][j] == bb && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }

        if (s[i][j] == aa && s[i][j + 1] == bb
         && s[i + 1][j] == aa && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }

        if (s[i][j] == bb && s[i][j + 1] == aa
         && s[i + 1][j] == aa && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }
        
        // other
        swap(aa, bb);

        if (s[i][j] == aa && s[i][j + 1] == aa
         && s[i + 1][j] == aa && s[i + 1][j + 1] == bb)
        {
          ans++;
          continue;
        }

        if (s[i][j] == aa && s[i][j + 1] == aa
         && s[i + 1][j] == bb && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }

        if (s[i][j] == aa && s[i][j + 1] == bb
         && s[i + 1][j] == aa && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }

        if (s[i][j] == bb && s[i][j + 1] == aa
         && s[i + 1][j] == aa && s[i + 1][j + 1] == aa)
        {
          ans++;
          continue;
        }
      }

    printf("%d\n", ans);
  }
  return 0;
}