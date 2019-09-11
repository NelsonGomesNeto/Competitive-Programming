#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

/* Tutorial:
  Heavy math happening here, still don't understand, but it's saved here
  Soon, I will stop and try to understand
*/

const int maxN = 32; int n, t;
int taps[maxN];
vector<vector<lli>> mat;
vector<pair<lli, lli>> block;
lli startState, endState, blockSize;

void buildBlock()
{
  lli now = startState;
  block.push_back({now, 0});
  for (int i = 0; i < blockSize; i ++)
  {
    lli bit = 0;
    for (int j = 0; j < t; j ++)
      bit ^= (now >> taps[j]) & 1LL;
    now = bit << (n - 1) | (now >> 1LL);
    block.push_back({now, i + 1});
  }
  sort(block.begin(), block.end());
}

void matMult(vector<vector<lli>> &a, vector<vector<lli>> &b)
{
  vector<vector<lli>> ans(a.size(), vector<lli>(b[0].size()));
  for (int i = 0; i < a.size(); i ++)
    for (int j = 0; j < b[0].size(); j ++)
    {
      for (int k = 0; k < b.size(); k ++)
        ans[i][j] += a[i][k] * b[k][j];
      ans[i][j] &= 1LL;
    }
  a = ans;
}
void matPow(vector<vector<lli>> &x, lli y)
{
  vector<vector<lli>> res(n, vector<lli>(n));
  for (int i = 0; i < n; i ++) res[i][i] = 1;
  while (y)
  {
    if (y & 1LL) matMult(res, x);
    matMult(x, x), y >>= 1LL;
  }
  x = res;
}

lli calc(lli now)
{
  lli ans = 0;
  for (int i = 0; i < n; i ++)
  {
    lli cnt = 0;
    for (int j = 0; j < n; j ++)
      cnt += mat[j][i] & (now >> (n - j - 1));
    ans = (ans << 1LL) | (cnt & 1);
  }
  return ans;
}

lli solve()
{
  for (lli i = 0, now = endState; i < blockSize; i ++, now = calc(now))
  {
    lli pos = lower_bound(block.begin(), block.end(), make_pair(now, 0LL)) - block.begin();
    DEBUG if (pos < block.size()) printf("now: %lld || %lld\n", now, block[pos].first);
    if (pos != block.size() && block[pos].first == now)
      return i * blockSize + block[pos].second;
  }
  return -1;
}

int main()
{
  while (scanf("%d %d", &n, &t) != EOF && n + t)
  {
    mat.clear(), block.clear();
    mat.resize(n, vector<lli>(n));

    for (int i = 0; i < n - 1; i ++)
      mat[i + 1][i] = 1;
    for (int i = 0; i < t; i ++)
    {
      scanf("%d", &taps[i]);
      mat[(n - taps[i]) % n][n - 1] = 1;
    }
    scanf("%llx %llx", &startState, &endState);

    blockSize = 1LL << ((n >> 1LL) + (n & 1LL));
    buildBlock();

    matPow(mat, blockSize);

    DEBUG {
      printf("blockSize: %lld\n", blockSize);
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          printf("%lld%c", mat[i][j], j < n - 1 ? ' ' : '\n');
      for (int i = 0; i < blockSize; i ++)
        printf("(%lld, %lld)%c", block[i].first, block[i].second, i < blockSize - 1 ? ' ' : '\n');
    }

    lli ans = solve();
    if (ans == -1) printf("*\n");
    else printf("%lld\n", ans);
  }
  return(0);
}