#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int mat[maxN][maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%d", &mat[i][j]);

    int trace = 0, r = 0, c = 0;
    for (int i = 0; i < n; i++)
      trace += mat[i][i];
    for (int i = 0; i < n; i++)
    {
      set<int> numbers;
      for (int j = 0; j < n; j++)
        numbers.insert(mat[i][j]);
      if (numbers.size() < n)
        r++;
    }
    for (int j = 0; j < n; j++)
    {
      set<int> numbers;
      for (int i = 0; i < n; i++)
        numbers.insert(mat[i][j]);
      if (numbers.size() < n)
        c++;
    }
    printf("Case #%d: %d %d %d\n", tt, trace, r, c);
  }
  return 0;
}