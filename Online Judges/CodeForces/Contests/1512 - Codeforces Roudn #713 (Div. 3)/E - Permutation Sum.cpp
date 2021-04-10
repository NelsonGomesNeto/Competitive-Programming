#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n, l, r, s;
const int maxSum = maxN * (maxN + 1) / 2;

// short memo[maxN][maxSum + 1], path[maxN][maxSum + 1];
// short solve(int i = 0, int selected = 0, int sum = 0)
// {
//   if (s == 7)
//     printf("\t%d %d %d - %d %d\n", i + 1, selected, sum, 0, 0);
//   if (selected >= r - l + 1 || sum == s)
//     return selected == r - l + 1 && sum == s;
//   if (sum >= s || i == n)
//     return 0;

//   short &ans = memo[i][sum];
//   if (ans != -1)
//     return ans;

//   short notPut = solve(i + 1, selected, sum);
//   short put = solve(i + 1, selected + 1, sum + i + 1);
//   path[i][sum] = put > notPut;
//   return ans = max(put, notPut);
// }
short memo[maxN + 1][maxSum + 1], path[maxN + 1][maxSum + 1];
int getMinimum(int i, int prv, int sum)
{
  while (i < r - l + 1)
  {
    sum += prv + 1;
    prv++;
    i++;
  }
  return sum;
}
int getMaximum(int i, int prv, int sum)
{
  prv = n;
  while (i < r - l + 1)
  {
    sum += prv;
    prv--;
    i++;
  }
  return sum;
}
short solve2(int i = 0, int prv = 0, int sum = 0)
{
  if (sum > s)
    return 0;
  if (i == r - l + 1 || sum == s)
    return sum == s && i == r - l + 1;
  if (!(getMinimum(i, prv, sum) <= s && getMaximum(i, prv, sum) >= s))
    return 0;

  short &ans = memo[prv][sum];
  if (ans != -1)
    return ans;

  ans = 0;
  for (int j = prv + 1; j <= n; j++)
  {
    short res = solve2(i + 1, j, sum + j);
    if (res)
    {
      path[prv][sum] = j;
      return ans = 1;
    }
  }

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &l, &r, &s);

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= s; j++)
        memo[i][j] = -1;

    short ans = solve2();
    if (ans)
    {
      vector<int> p(n, -1);
      set<int> missing;
      for (int i = 1; i <= n; i++)
        missing.insert(i);

      for (int i = l - 1, prv = 0, sum = 0; i < r; i++)
      {
        int toPut = path[prv][sum];
        sum += toPut, p[i] = toPut, missing.erase(toPut);
        prv = toPut;
      }

      for (int j = 0; !missing.empty(); j++)
      {
        while (j < n && p[j] != -1) j++;
        p[j] = *missing.begin();
        missing.erase(p[j]);
      }

      lli done = 0;
      for (int i = l - 1; i < r; i++)
        done += p[i];
      assert(done == s);
      set<int> has;
      for (int i = 0; i < n; i++)
      {
        assert(!has.count(p[i]));
        has.insert(p[i]);
      }
      assert(has.size() == n);

      for (int i = 0; i < n; i++)
        printf("%d%c", p[i], i < n - 1 ? ' ' : '\n');
    }
    else
      printf("-1\n");
  }
  return 0;
}
