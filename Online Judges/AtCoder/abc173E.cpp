#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7, inf = LONG_LONG_MAX;
const int maxN = 2e5; int n, k;
lli a[maxN];
vector<lli> neg, pos;
vector<double> nacc, pacc;

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    neg.clear(), pos.clear(); int zeros = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      if (a[i] < 0) neg.push_back(a[i]);
      else if (a[i] == 0) zeros++;
      else pos.push_back(a[i]);
    }
    sort(neg.begin(), neg.end());
    sort(pos.begin(), pos.end());
    reverse(pos.begin(), pos.end());

    nacc.resize(neg.size() + 1);
    nacc[0] = 0;
    for (int i = 0; i < neg.size(); i++)
      nacc[i + 1] = nacc[i] + log10(-neg[i]);

    pacc.resize(pos.size() + 1);
    pacc[0] = 0;
    for (int i = 0; i < pos.size(); i++)
      pacc[i + 1] = pacc[i] + log10(pos[i]);

    lli hehe = 0;
    if (neg.size() + pos.size() >= k)
    {
      double ans = -1; int ww = 0, wi, wj;
      for (int i = 0; i <= pos.size() && i <= k; i++)
        if (!((k - i) & 1) && (k - i) <= neg.size())
        {
          double w = pacc[i] + nacc[k - i];
          if (w > ans)
            ans = w, wi = i, wj = k - i, ww = 1;
        }
      if (ww)
      {
        hehe = 1;
        for (int i = 0; i < wi; i++)
          hehe = hehe * pos[i] % mod;
        for (int j = 0; j < wj; j++)
          hehe = (hehe * neg[j] % mod + mod) % mod;
      }

      if (ww == 0 && zeros == 0)
      {
        reverse(pos.begin(), pos.end());
        reverse(neg.begin(), neg.end());

        nacc.resize(neg.size() + 1);
        nacc[0] = 0;
        for (int i = 0; i < neg.size(); i++)
          nacc[i + 1] = nacc[i] + log(-neg[i]);

        nacc.resize(neg.size() + 1);
        nacc[0] = 0;
        for (int i = 0; i < neg.size(); i++)
          nacc[i + 1] = nacc[i] + log(-neg[i]);

        ans = inf;
        for (int i = 0; i <= pos.size() && i <= k; i++)
          if (((k - i) & 1) && (k - i) <= neg.size())
          {
            double w = pacc[i] + nacc[k - i];
            if (w < ans)
              ans = w, wi = i, wj = k - i, ww = 1;
          }
        if (ww)
        {
          hehe = 1;
          for (int i = 0; i < wi; i++)
            hehe = hehe * pos[i] % mod;
          for (int j = 0; j < wj; j++)
            hehe = (hehe * neg[j] % mod + mod) % mod;
        }
      }
    }

    printf("%lld\n", hehe);
  }
  return 0;
}