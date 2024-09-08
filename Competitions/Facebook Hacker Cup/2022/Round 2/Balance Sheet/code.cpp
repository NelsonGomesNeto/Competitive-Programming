#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
lli a[maxN], b[maxN];
lli x[maxN], y[maxN];
map<int, vector<pair<lli, int>>> sells;
map<int, vector<pair<lli, int>>> buys;

vector<int> graph[maxN];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %d", &n, &k);
    buys.clear(), sells.clear();
    for (int i = 0; i < n; ++i)
    {
      scanf("%lld %lld %lld %lld", &a[i], &b[i], &x[i], &y[i]);
      buys[a[i]].push_back({x[i], i}), sells[b[i]].push_back({y[i], i});
    }

    for (auto& b : buys)
      sort(b.second.begin(), b.second.end());
    for (auto& s : sells)
      sort(s.second.begin(), s.second.end());

    priority_queue<pair<lli, int>> pq;
    for (auto& s : sells)
    {
      if (!buys.count(s.first)) continue;

      
    }

    printf("Case #%d: \n", testCase);
  }
  return 0;
}
