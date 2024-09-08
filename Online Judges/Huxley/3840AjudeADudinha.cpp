#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k, p;
vector<int> primes;
bool notPrime[maxN + 1];
int memo[maxN + 1];
vector<int> missing[maxN + 1];

int main()
{
  memset(memo, 0, sizeof(memo));
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i++)
  {
    if (memo[i] == 0) memo[i] = i & 1;
    if (!notPrime[i] && (lli)i*i <= maxN)
    {
      for (int j = i * i; j <= maxN; j += i)
      {
        notPrime[j] = true;
        if (j / i % i == 0 && i != 2) memo[j] = -1;
        else missing[j / i].push_back(j);
      }
    }
  }
  for (int i = 0; i <= maxN; i++)
    for (int m: missing[i])
      if (memo[i] == -1 || memo[m / i] == -1) memo[m] = -1;
      else memo[m] = memo[i] + memo[m / i];

  for (int i = 0; i <= maxN; i++)
    if (!notPrime[i])
      primes.push_back(i);

  while (~scanf("%d %d %d", &n, &k, &p))
  {
    int ans = -1, cnt = 0;
    for (int i = n; i < k; i++)
    {
      bool valid = true;
      int curr = i, c = 0;
      // sqrt(n) check
      // for (int pp: primes)
      // {
      //   if (pp > curr) break;

      //   if (curr % pp == 0)
      //   {
      //     if (curr / pp % pp == 0 && pp != 2)
      //     {
      //       valid = false;
      //       break;
      //     }
      //     c += (pp != 2);
      //     while (curr % pp == 0) curr /= pp;
      //   }
      // }

      // if (valid && c != memo[i]) printf("%d - %d - %d\n", i, c, memo[i]);
      c = memo[i];
      valid &= c == p && c >= 0;

      DEBUG printf("\t%d %d %d\n", i, valid, c);
      if (valid)
      {
        cnt++;
        if (ans == -1) ans = i;
      }
    }

    if (ans == -1) printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    else printf("%d %d\n", ans, cnt - 1);
  }
  return 0;
}