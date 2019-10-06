#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n, m;

int a[maxN], b[maxN];

int memo[maxN + 1][maxN + 1];
int lcs(int A[], int B[])
{
  for (int i = n - 1; i >= 0; i --)
    for (int j = n - 1; j >= 0; j --)
      if (A[i] == B[j])
        memo[i][j] = 1 + memo[i + 1][j + 1];
      else
        memo[i][j] = max(memo[i + 1][j], memo[i][j + 1]);
  return memo[0][0];
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
  {
    ldouble x;
    scanf("%d %Lf", &a[i], &x);
  }
  memcpy(b, a, sizeof(a));
  sort(a, a+n);

  int ans = n - lcs(a, b);
  printf("%d\n", ans);

  return 0;
}