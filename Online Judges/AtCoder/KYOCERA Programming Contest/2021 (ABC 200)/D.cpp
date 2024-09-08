#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200; int n;
const int mod = 200;
int a[maxN];

int memo[maxN][maxN][8], path[maxN][maxN][8];
int solve(int i = 0, int sum = 0, int equal = true, int hasB = false, int hasC = false)
{
  if (sum == 0 && !equal && hasB && hasC) return 1;
  if (i == n) return 0;

  int mask = (equal << 2) | (hasB << 1) | hasC;
  int &ans = memo[i][sum][mask], &choice = path[i][sum][mask];
  if (ans != -1) return ans;

  int both = solve(i + 1, sum, equal, true, true);
  int atB = solve(i + 1, (sum + a[i]) % mod, false, true, hasC);
  int atC = solve(i + 1, ((sum - a[i]) % mod + mod) % mod, false, hasB, true);
  if (both >= atB && both >= atC) ans = both, choice = 3;
  else if (atB >= atC) ans = atB, choice = 1;
  else ans = atC, choice = 2;

  return ans;
}

void printArr(vector<int> &arr)
{
  printf("%d", (int)arr.size());
  for (int i: arr) printf(" %d", i + 1);
  printf("\n");
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i] %= mod;
    }

    memset(memo, -1, sizeof(memo)), memset(path, -1, sizeof(path));
    int ans = solve();
    if (ans == 0) printf("No\n");
    else
    {
      printf("Yes\n");
      vector<int> b, c;
      for (int i = 0, sum = 0, equal = 1, hasB = 0, hasC = 0; i < n; i++)
      {
        int mask = (equal << 2) | (hasB << 1) | hasC;
        int &choice = path[i][sum][mask];
        if (choice == -1) break;

        if (choice & 1)
          b.push_back(i), sum = (sum + a[i]) % mod, hasB = 1;
        if (choice & 2)
          c.push_back(i), sum = ((sum - a[i]) % mod + mod) % mod, hasC = 1;
        if (choice != 3)
          equal = 0;
      }

      printArr(b);
      printArr(c);
    }
  }
  return 0;
}