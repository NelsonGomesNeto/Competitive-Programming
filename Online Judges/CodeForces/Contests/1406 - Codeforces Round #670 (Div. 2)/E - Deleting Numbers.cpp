#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Did you also wonder why you can make query(A, *1*)? That's a key query
  And the fact that we can emulate the judge procedure

  There are 9592, we can query for all primes, but not much after that

  x = product p[i]^e[i]

  Notice that after applying query(B, p[i]):
    if (ourCountAfterThat() != query(A, 1))
      p[i] must be a multiple of x
    But we can't apply query(B, p[i]) and query(A, 1) for all primes
  Also notice that after applying query(B, p[lo : hi]) (a list of primes)
    if (ourCountAfterThat() != query(A, 1))
      some primes in p[lo : hi] must be multiples of x
    We can always iterate over lo and hi, and check query(A, p[i]) > 0,
    but will cost hi - lo + 1 queries

  Let's minimize the amount of groups and the amount of iterations in a group by:
  sqrt(9592) ~= 98, hehe (I don't know if this is the best; but this will do)
  Split the primes into groups of size sqrt(9592)

  ans = 1
  for g in groups (reverse them to make sure that you find the biggest primes first):
    for p in g:
      if (ans * p <= n):
        query(B, p)
        updateOurCount
    if (ourCount != query(A, 1)): // this will always trigger after ans != 1
      for p in g:
        if (ans * primes[i] <= n && query(A, p)):
          ans *= findTheBiggestPot(p)

  You will keep removing the biggest primes until you find the first biggest
  group of primes that have a multiple of x. From there on, you will be blind
  Since there's no way to know if a group contains a prime multiple of x, since
  x will always be present. So, cut the useless queries (ans * p > n): gg
*/

const int maxN = 1e5, maxQ = 1e4; int n;
bool notPrime[maxN + 1];
vector<int> primes;
bool all[maxN + 1]; int allSum;

int qs = 0;
int query(char op, int num)
{
  assert(qs + 1 <= maxQ);
  qs++;
  printf("%c %d\n", op, num); fflush(stdout);
  int res; scanf("%d", &res);
  return res;
}

lli ans = 1;
int getPrimePot(int p)
{
  lli currP = (lli)p * p, foundP = p;
  while (currP <= n)
  {
    if (query('A', currP)) foundP = currP;
    currP *= p;
  }
  return foundP;
}

void blockSearch(int lo, int hi)
{
  for (int i = lo; i <= hi; i++)
  {
    if (ans * primes[i] > n) continue;
    query('B', primes[i]);
    for (int j = 1; j * primes[i] <= n; j++)
    {
      allSum -= all[j * primes[i]];
      all[j * primes[i]] = false;
    }
  }

  int curr = query('A', 1);
  if (curr != allSum) // yes, will always trigger after ans != 1
    for (int i = lo; i <= hi; i++)
      if (ans * primes[i] <= n && query('A', primes[i]))
        ans *= getPrimePot(primes[i]);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  scanf("%d", &n);

  for (int i = 0; i <= n; i++) all[i] = true;
  allSum = n;

  for (int i = 2; i <= n; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= n; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  ans = 1;

  int firstBlockSize = sqrt(primes.size());
  vector<pair<int, int>> blocks;
  for (int i = 0; i * firstBlockSize + (i > 0) < primes.size(); i++)
    blocks.push_back({i * firstBlockSize + (i > 0), min((int)primes.size() - 1, (i + 1) * firstBlockSize)});
  reverse(blocks.begin(), blocks.end());

  for (auto [lo, hi]: blocks)
    blockSearch(lo, hi);

  printf("C %lld\n", ans); fflush(stdout);

  return 0;
}
