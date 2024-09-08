#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxN = 1e5; int n, k;
vector<vector<int>> rrs;
map<vector<int>, int> cnt;
ordered_set<pair<vector<int>, int>> pcs;

int calc(vector<int> &rs, ordered_set<pair<vector<int>, int>>::iterator lo = pcs.begin(), ordered_set<pair<vector<int>, int>>::iterator hi = prev(pcs.end()), int i = 0, vector<int> lol = {})
{
  DEBUG printf("\there %d\n", i);

  if (i == k)
  {
    int ll = (int)pcs.order_of_key(make_pair(lol, -1));
    lol.back()++;
    int hh = (int)pcs.order_of_key(make_pair(lol, 1e9));
    DEBUG printf("%d - %d %d\n", i, ll, hh);
    return hh - ll;
  }

  int ans = 0;
  vector<int> req = lol;
  for (int hehe = rs[i]; hehe <= 8; hehe++)
  {
    req[i] = hehe;

    // for (int j = i + 1; j < k; j++) req[j] = -1;
    // lo = pcs.lower_bound(make_pair(req, -1));

    // for (int j = i + 1; j < k; j++) req[j] = 1e9;
    // hi = pcs.lower_bound(make_pair(req, 1e9));

    // if (lo == pcs.end() || lo->first[i] != hehe || hi == pcs.end() || hi->first[i] != hehe) continue;

    int res = calc(rs, lo, hi, i + 1, req);
    ans += res;
    DEBUG printf("\t\t%d %d %d\n", i, hehe, res);
  }
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    rrs.clear(), pcs.clear();

    for (int i = 0; i < n; i++)
    {
      char op; int r; scanf(" %c %d", &op, &r);
      if (op == 'D')
      {
        DEBUG printf("\t%d %d %d\n", r, (int)rrs.size(), (int)pcs.size()); fflush(stdout);
        r--;
        auto it = pcs.lower_bound(make_pair(rrs[r], -1));
        pcs.erase(it);
        DEBUG printf("\t%d\n", (int)pcs.size());
      }
      else
      {
        rrs.push_back(vector<int>(k, 0));
        for (int j = 0; j < r; j++)
        {
          int g; scanf("%d", &g); g--;
          rrs.back()[g]++;
        }

        if (op == 'C')
          pcs.insert(make_pair(rrs.back(), cnt[rrs.back()]++));
        else
        {
          int ans = calc(rrs.back());
          printf("%d\n", ans);
        }
      }
    }
  }
  return 0;
}