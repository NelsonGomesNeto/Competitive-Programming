#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int k;

int main()
{
  int a = 262144 - 1;
  int b = 131072;
  while (scanf("%d", &k) != EOF)
  {
    printf("3 3\n");
    int mat[3][3];
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mat[i][j] = a;
    
    mat[0][1] = mat[2][2] = k;
    mat[1][0] = b;

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        printf("%d%c", mat[i][j], j < 3 - 1 ? ' ' : '\n');
  }
  return 0;
}
