#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, nn;
const lli mod = 1e9 + 7;

string getStr(int num)
{
  string a = num == 0 ? "0" : "";
  while (num)
  {
    a += '0' + (num % 10);
    num /= 10;
  }
  reverse(a.begin(), a.end());
  return a;
}

int wantedMask = (1 << 3) - 1;
int digitMask[16];

lli memo[maxN][1 << 3];
lli solve(int i = 0, int hasMask = 0)
{
  // if (hasMask == wantedMask) printf("%s\n", lol.c_str());
  if (i == n) return hasMask == wantedMask;
  if (memo[i][hasMask] != -1) return memo[i][hasMask];

  lli ans = 0;
  for (int k = i == 0; k < 16; k++)
    ans = (ans + solve(i + 1, hasMask | digitMask[k])) % mod;
  return memo[i][hasMask] = ans;
}

int main()
{
  digitMask[0] = 1 << 0, digitMask[1] = 1 << 1, digitMask[10] = 1 << 2;
  while (scanf("%d", &nn) != EOF)
  {
    lli ans = 0;
    for (n = 3; n <= nn; n++)
    {
      memset(memo, -1, sizeof(memo));
      ans = (ans + solve()) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}