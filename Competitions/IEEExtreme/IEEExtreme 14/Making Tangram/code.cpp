#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 62; int n;
char mat[maxN][maxN + 1];
string alf;

int main()
{
  for (char i = 'a'; i <= 'z'; i++) alf.push_back(i);
  for (char i = 'A'; i <= 'Z'; i++) alf.push_back(i);
  for (char i = '0'; i <= '9'; i++) alf.push_back(i);

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    memset(mat, '\0', sizeof(mat));

    if (n <= 3) printf("impossible\n");
    else if (n == 4) printf("aaaa\nbbbc\nbddc\nddcc\n");
    else
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          mat[i][j] = ' ';

      mat[0][0] = alf[0];
      for (int i = 0; i < n - 2; i++)
        for (int j = 0; j < n; j++)
        {
          int ii = i + (j + i >= n ? 1 : 0);
          int jj = j + i >= n ? j : j + 1; 
          mat[ii][jj] = alf[i];
          // printf("\t%c %d %d\n", mat[ii][jj], ii, jj);
        }

      for (int j = 1; j < n; j++)
        mat[n - 1][j] = alf[n - 2];
      mat[n - 2][2] = alf[n - 2];

      for (int i = 1; i < n; i++)
        mat[i][0] = alf[n - 1];
      mat[n - 2][1] = alf[n - 1];

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          printf("%c", mat[i][j]);
        printf("\n");
      }
    }
  }
  return 0;
}