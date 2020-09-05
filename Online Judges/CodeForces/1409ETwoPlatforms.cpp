#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
vector<lli> xs, xs2;

struct Block
{
  int lo, hi, quantity;
};
vector<Block> blocks;
int maximum[maxN + 1];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      scanf("%d %lld", &n, &k);

      xs.clear();
      for (int i = 0; i < n; i++)
      {
        lli x; scanf("%lld", &x);
        xs.push_back(x);
      }
      for (int i = 0; i < n; i++)
      {
        lli y; scanf("%lld", &y);
      }

      sort(xs.begin(), xs.end());
      // xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));
      DEBUG {
        printf("\t");
        for (int i = 0; i < xs.size(); i++)
          printf("%lld%c", xs[i], i < (int)xs.size() - 1 ? ' ' : ' ');
        printf("\n");
      }

      blocks.clear();
      for (int i = xs.size() - 1; i >= 0; i--)
      {
        int j = lower_bound(xs.begin(), xs.end(), xs[i] - k) - xs.begin();
        int quantity = i - j + 1;
        blocks.push_back(Block{j, i, quantity});
      }
      reverse(blocks.begin(), blocks.end());

      maximum[0] = 0;
      for (int i = 0; i < xs.size(); i++)
        maximum[i + 1] = max(maximum[i], blocks[i].quantity);

      int ans = 0;
      for (int i = xs.size() - 1; i >= 0; i--)
      {
        int j = lower_bound(xs.begin(), xs.end(), xs[i] - k) - xs.begin();
        int quantity = i - j + 1;
        ans = max(ans, quantity + maximum[j]);
      }

      printf("%d\n", ans);
    }
  return 0;
}