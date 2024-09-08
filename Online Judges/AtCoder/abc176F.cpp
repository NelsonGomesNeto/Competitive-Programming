#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 6e3, maxX = 2e3 + 1; int n;
int arr[maxN];

int memo[maxN][maxX][3][3];
// Do the oposite: leave one out
int permutations[6][3] = {
  {0, 1, 2},
  {0, 2, 1},
  {1, 0, 2},
  {1, 2, 0},
  {2, 0, 1},
  {2, 1, 0}
};
int solve(int i = 0, int leftOut = 0, int cnt = 0)
{
  if (i + 2 >= n - 1)
  {
    if (i + 1 == n - 1) return leftOut == arr[i] && leftOut == arr[i + 1];
    return i + 2 == n - 1 ?
      (arr[i] == arr[i + 1] && arr[i] == arr[i + 2])
      || (leftOut == arr[i] && leftOut == arr[i + 1])
      || (leftOut == arr[i + 1] && leftOut == arr[i + 2])
      || (leftOut == arr[i] && leftOut == arr[i + 2])
        : 0;
  }

  int ans = 0;
  if (arr[i] == arr[i + 1] && arr[i] == arr[i + 2])
    ans = max(ans, 1 + solve(i + 3, leftOut));

  int temp[3] = {arr[i], arr[i + 1], arr[i + 2]};
  for (int j = 0; j < 6; j++)
  {
    for (int k = 0; k < 3; k++)
      arr[i + k] = temp[permutations[j][k]];
    ans = max({ans, solve(i + 1, arr[i]), solve(i + 1, leftOut)});
  }
  for (int k = 0; k < 3; k++)
    arr[i + k] = temp[k];

  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    n = 3*n;
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}