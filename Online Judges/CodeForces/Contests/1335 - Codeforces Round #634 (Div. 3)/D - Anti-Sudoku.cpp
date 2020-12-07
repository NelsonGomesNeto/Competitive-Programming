#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    char sudoku[9][10];
    for (int i = 0; i < 9; i++)
      scanf(" %s", sudoku[i]);

    for (int k = 0, i = 0, j = 0; k < 9; k++)
    {
      sudoku[i][j] = (sudoku[i][j] - '0') % 9 + 1 + '0';
      j = (j + 3 + (i % 3 == 2)) % 9;
      i++;
    }

    for (int i = 0; i < 9; i++)
      printf("%s\n", sudoku[i]);
  }
  return 0;
}