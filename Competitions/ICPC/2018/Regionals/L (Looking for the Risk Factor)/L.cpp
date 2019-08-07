#include <bits/stdc++.h>
using namespace std;

/* Explanation:
We will precalculate the answer for every N, but in two different ways
First, for every prime smaller than 1000, there are less than 200 of them [primeIndex][maxN]
Second, for every multiple of 1000, there are 100 of them [k / 1000][maxN]
  In order to precalculate each of them, you will need an array that stores what is the
  biggest prime divisor of a number, remember that you can find all divisores until the sqrt(n)

To answer the first kind of query, just print(memo1[findPos(primes, k)][n])
To answer the second kind of query, answer = memo2[k / 1000][n], with this we will have the answer
until 1000 * floor(k/1000), but we still need to reach k. For each prime between 1000 * floor(k/1000) + 1 and k
add n / prime to the answer (why?). Now you can print it.
why: First, remember that (x/y) is how many times y can divide x. Now, notice that "prime" is at least 1000
and 1000^2 > 100000. So there's no other prime number bigger than "prime" that can be multiplied by it and reach n.
Concluding: we only need to add the numbers that are multiples of "prime" and smaller than n.
*/

const int maxN = 1e5, allPrimes = 1e4;
bool notPrime[maxN + 1];
vector<int> primes;
int memoSmall[200][maxN + 1], memo[100 + 1][maxN + 1], biggestDivisor[maxN + 1];

int findPos(vector<int> &array, int target)
{
  int pos = lower_bound(array.begin(), array.end(), target) - array.begin();
  return(pos - (array[pos] > target));
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++) for (int j = 2; i*j <= maxN; j ++) notPrime[i*j] = true;
  for (int i = 2; i <= maxN; i ++) if (!notPrime[i]) primes.push_back(i);

  for (int i = 2; i <= maxN; i ++)
  {
    if (notPrime[i])
    {
      int end = sqrt(i);
      for (int &p: primes)
      {
        if (p > end) break;
        if (i % p == 0) biggestDivisor[i] = max(biggestDivisor[i], max(p, biggestDivisor[i / p]));
      }
    }
    else
      biggestDivisor[i] = i;
  }

  for (int j = 1; j <= 100; j ++)
  {
    for (int n = 2; n <= j*1000; n ++) memo[j][n] = n - 1;
    for (int n = j*1000 + 1; n <= maxN; n ++) memo[j][n] = memo[j][n - 1] + (biggestDivisor[n] <= j*1000);
  }
  for (int p = 0; primes[p] < 1000; p ++)
  {
    for (int n = 2; n <= primes[p]; n ++) memoSmall[p][n] = n - 1;
    for (int n = primes[p] + 1; n <= maxN; n ++) memoSmall[p][n] = memoSmall[p][n - 1] + (biggestDivisor[n] <= primes[p]);
  }

  int q; scanf("%d", &q);
  while (q --)
  {
    int n, k; scanf("%d %d", &n, &k);
    if (k < 1000) printf("%d\n", memoSmall[findPos(primes, k)][n]);
    else
    {
      int m = k / 1000;
      int ans = memo[m][n];
      for (int i = findPos(primes, m*1000) + 1; i < primes.size() && primes[i] <= k; i ++)
        ans += n / primes[i];
      printf("%d\n", ans);
    }
  }
  return(0);
}