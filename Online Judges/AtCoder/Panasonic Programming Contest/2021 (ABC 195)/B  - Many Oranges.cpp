#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b, w;
const int maxW = 1e6;
int memo[maxW + 1];
int minSolve(int t = 0)
{
  if (t > w)
    return 1e7;
  if (t == w)
    return 0;
  int &ans = memo[t];
  if (ans != -1)
    return ans;

  ans = 1e7;
  for (int i = b; i >= a; i--)
  {
    int res = 1 + minSolve(t + i);
    if (res < 1e7 && res > ans)
      break;
    ans = min(ans, res);
  }
  return ans;
}
int maxSolve(int t = 0)
{
  if (t > w)
    return -1e7;
  if (t == w)
    return 0;
  int &ans = memo[t];
  if (ans != -1)
    return ans;

  ans = -1e7;
  for (int i = a; i <= b; i++)
  {
    int res = 1 + maxSolve(t + i);
    if (res > -1e7 && res < ans)
      break;
    ans = max(ans, res);
  }
  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &a, &b, &w))
  {
    w *= 1000;

    memset(memo, -1, sizeof(memo));
    int minAns = minSolve();
    memset(memo, -1, sizeof(memo));
    int maxAns = maxSolve();

    if (minAns >= 1e7)
      printf("UNSATISFIABLE\n");
    else
      printf("%d %d\n", minAns, maxAns);
  }
  return 0;
}