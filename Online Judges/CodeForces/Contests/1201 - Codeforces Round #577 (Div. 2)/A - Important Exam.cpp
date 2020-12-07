#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1000, maxM = 1000; int n, m;
char students[maxN][maxM + 1];
int points[maxN];
int cnt[maxM][5];

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    scanf("%s", students[i]);
  for (int i = 0; i < m; i ++)
    scanf("%d", &points[i]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      cnt[j][students[i][j] - 'A'] ++;

  int ans = 0;
  for (int i = 0; i < m; i ++)
    ans += points[i] * max({cnt[i][0], cnt[i][1], cnt[i][2], cnt[i][3], cnt[i][4]});
  printf("%d\n", ans);

  return(0);
}
