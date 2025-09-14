#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
int n;
int a[maxN];

// O(n * lg(n))
const int kInf = 1e9;
vector<int> lis() {
  vector<int> seq(n + 1, kInf), seq_to_i(n + 1, -1), prv(n + 1, -1);
  seq[0] = -kInf;
  for (int i = 0; i < n; i++) {
    const int l = upper_bound(seq.begin(), seq.end(), a[i]) - seq.begin();
    if (seq[l - 1] >= a[i] || a[i] >= seq[l]) continue;
    seq[l] = a[i], seq_to_i[l] = i;
    prv[i] = seq_to_i[l - 1];
  }

  std::vector<int> ans;
  const int l = prev(lower_bound(seq.begin(), seq.end(), kInf)) - seq.begin();
  ans.push_back(seq[l]);
  for (int i = prv[seq_to_i[l]]; i >= 0; i = prv[i]) ans.push_back(a[i]);
  std::reverse(ans.begin(), ans.end());

  return ans;
}

// O(n^2)
int memo[maxN][maxN + 1];
int path[maxN][maxN + 1];  // 0 - ignore, 1 - put
int lis2(int i = 0, int prv = n) {
  if (i == n) return 0;
  int &ans = memo[i][prv];
  if (ans != -1) return ans;

  int ignore = lis2(i + 1, prv), put = -1;
  if (prv == n || a[i] > a[prv]) put = lis2(i + 1, i) + 1;
  path[i][prv] = put >= ignore;

  return ans = max(ignore, put);
}
int memo2[maxN], prvmemo[maxN];
int lis3() {
  memset(memo2, 0, sizeof(memo2));
  memset(prvmemo, -1, sizeof(prvmemo));
  memo2[0] = 1;
  for (int i = 1; i < n; i++) {
    memo2[i] = 1;
    for (int prv = 0; prv < i; prv++)
      if (a[i] > a[prv] && memo2[prv] + 1 >= memo2[i]) {
        memo2[i] = memo2[prv] + 1;
        prvmemo[i] = prv;
      }
  }
  return *max_element(memo2, memo2 + n);
}

// value mapping
// Sequence is h[i], value is a[i]
// You want a increasing sequence whose value sum is maximum
int lis4() {
  // segtree = Segtree<Data>(maxH + 1, nil);
  // for (int i = 0; i <= maxH; i++)
  //   segtree.data[i] = nil;
  // segtree.build();

  // segtree.update(h[0], Data{a[0]});
  // for (int i = 1; i < n; i++)
  // {
  //   Data bestPrv = segtree.query(0, h[i]);
  //   segtree.update(h[i], Data{max(a[i], bestPrv.value + a[i])});
  // }
  // return segtree.query(0, maxH).value;
  return -1;
}

int main() {
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    vector<int> ans = lis();
    printf("LIS (%d):\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
      printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');

    printf("--------------\n");

    memset(memo, -1, sizeof(memo));
    lis2();
    vector<int> ans2;
    for (int i = 0, prv = n; i < n; i++)
      if (path[i][prv]) prv = i, ans2.push_back(a[i]);
    printf("LIS (%d):\n", (int)ans2.size());
    for (int i = 0; i < ans2.size(); i++)
      printf("%d%c", ans2[i], i < ans2.size() - 1 ? ' ' : '\n');

    printf("--------------\n");
    lis3();
    vector<int> ans3;
    int pos = max_element(memo2, memo2 + n) - memo2;
    while (pos != -1) {
      ans3.push_back(a[pos]);
      pos = prvmemo[pos];
    }
    reverse(ans3.begin(), ans3.end());
    printf("LIS (%d):\n", (int)ans3.size());
    for (int i = 0; i < ans3.size(); i++)
      printf("%d%c", ans3[i], i < ans3.size() - 1 ? ' ' : '\n');
  }
  return 0;
}