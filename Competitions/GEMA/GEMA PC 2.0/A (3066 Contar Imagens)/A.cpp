#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, m, nn, mm;
vector<vector<int>> img1, img2;
void print(vector<vector<int>> &a)
{
  for (int i = 0; i < a.size(); i ++)
    for (int j = 0; j < a[i].size(); j ++)
      printf("%2d%c", a[i][j], j < a[i].size() - 1 ? ' ' : '\n');
}

bool match(int i, int j)
{
  for (int ii = 0; ii < nn; ii ++)
    for (int jj = 0; jj < mm; jj ++)
      if (img1[i + ii][j + jj] != img2[ii][jj])
        return false;
  return true;
}
int solve()
{
  int ans = 0;
  for (int i = 0; i + (nn - 1) < n; i ++)
    for(int j = 0; j + (mm - 1) < m; j ++)
      ans += match(i, j);
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    img1.clear();
    img1.resize(n, vector<int>(m));
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        scanf("%d", &img1[i][j]);
    DEBUG print(img1);

    scanf("%d %d", &nn, &mm);
    img2.clear();
    img2.resize(nn, vector<int>(mm));
    for (int i = 0; i < nn; i ++)
      for (int j = 0; j < mm; j ++)
        scanf("%d", &img2[i][j]);
    DEBUG print(img2);

    printf("%d\n", solve());
  }
  return 0;
}