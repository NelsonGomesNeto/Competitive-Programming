#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e5;
bool notPrime[maxN + 1];
int biggestDivisor[maxN + 1];

int binSearch(vector<int> &a, int target)
{
  int lo = 0, hi = a.size() - 1, mid;
  while (lo < hi)
  {
    mid = (lo + hi) >> 1;
    if (a[mid] < target) lo = mid + 1;
    // else hi = mid;
    else if (a[mid] > target) hi = mid;
    else return(mid);
  }
  if (a[lo] > target) lo --;
  return(lo);
}
int binSearchAns(vector<pair<int, int>> a, int target)
{
  int lo = 0, hi = a.size() - 1, mid;
  while (lo < hi)
  {
    mid = (lo + hi) >> 1;
    if (a[mid].first < target) lo = mid + 1;
    // else hi = mid;
    else if (a[mid].first > target) hi = mid;
    else return(a[mid].second);
  }
  return(a[lo].second);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++)
    for (int j = 2; i*j <= maxN; j ++)
      notPrime[i*j] = true;
  vector<int> primes;
  for (int i = 2; i <= maxN; i ++) if (!notPrime[i]) primes.push_back(i);

  vector<int> nsOfPrimes[maxN + 1];
  for (int i = 2; i <= maxN; i ++)
  {
    if (!notPrime[i]) biggestDivisor[i] = i;
    else
    {
      int end = sqrt(i);
      for (int p: primes)
      {
        if (p > end) break;
        if (i % p == 0)
          biggestDivisor[i] = max(biggestDivisor[i], max(p, biggestDivisor[i / p]));
      }
    }
    nsOfPrimes[biggestDivisor[i]].push_back(i);
  }

  int q; scanf("%d", &q);
  pair<int, int> queries[q];
  vector<pair<int, int>> eachNK[maxN + 1];
  int lastK[maxN + 1]; memset(lastK, -1, sizeof(lastK));
  for (int i = 0; i < q; i ++)
  {
    int n, k; scanf("%d %d", &n, &k);
    queries[i].first = n, queries[i].second = k;
    if (lastK[n] == -1) lastK[n] = k;
    else lastK[n] = max(lastK[n], k);
    eachNK[n].push_back({k, 0});
  }
  for (int i = 2; i <= maxN; i ++) if (lastK[i] != -1) sort(eachNK[i].begin(), eachNK[i].end());

  int total = 0, prv = 0, e, limit, n2, k2;
  for (int j = 2; j <= maxN; j ++)
    if (lastK[j] != -1)
    {
      vector<pair<int, int>>::iterator it = eachNK[j].begin(), end = -- eachNK[j].end();
      while (it <= end && end->first >= j) (end--)->second = j - 1;
      if (it > end) continue;

      total = 0, limit = min(end->first, j), n2 = j >> 1, k2 = end->first >> 1;
      for (int &p: primes)
      {
        if (p > limit) break;
        else if (p > n2) e = 0;
        else if (nsOfPrimes[p][nsOfPrimes[p].size() - 1] <= j) e = nsOfPrimes[p].size() - 1;
        else
        {
          if (p > 1000) e = j / p - 1;
          else
          {
            e = lower_bound(nsOfPrimes[p].begin(), nsOfPrimes[p].end(), j) - nsOfPrimes[p].begin();
            if (nsOfPrimes[p][e] > j) e --;
          }
        }
        total += e + 1;
        while (p > it->first) (it ++)->second = prv;
        it->second = prv = total;
      }
      while (it <= end) (it ++)->second = total;
    }

  for (auto query: queries)
    printf("%d\n", binSearchAns(eachNK[query.first], query.second));

  return(0);
}