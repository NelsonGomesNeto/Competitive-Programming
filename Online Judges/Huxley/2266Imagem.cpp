#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    char image[n][m + 1];
    for (int i = 0; i < n; i ++)
    {
      getchar();
      scanf("%[^\n]", image[i]);
    }
    int bigN, bigM; scanf("%d %d", &bigN, &bigM);
    char bigImage[bigN][bigM + 1]; memset(bigImage, '\0', sizeof(bigImage));
    int dy = bigN / n, dx = bigM / m;
    for (int i = 0, ii = 0, jj = 0; i < n; i ++)
      for (int y = 0; y < dy; y ++, ii ++, jj = 0)
        for (int j = 0; j < m; j ++)
          for (int x = 0; x < dx; x ++, jj ++)
            bigImage[ii][jj] = image[i][j];
    for (int i = 0; i < bigN; i ++) printf("%s\n", bigImage[i]);
    printf("\n");
  }
  return(0);
}
