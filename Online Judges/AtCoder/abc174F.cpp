#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n, q;
int c[maxN];

const int blockSize = 100;
struct Block
{
  int lo, hi;
  bitset<maxN> numbers;
};
vector<Block> blocks;

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    blocks.clear();
    for (int i = 0; i < n; i++)
      scanf("%d", &c[i]);

    for (int i = 0; i < n / blockSize; i++)
    {
      Block b = Block{i * blockSize, (i + 1) * blockSize - 1, bitset<maxN>(0)};
      for (int j = i * blockSize, hehe = 0; hehe < blockSize; hehe++, j++)
        if (!b.numbers[c[j] - 1])
          b.numbers.flip(c[j] - 1);
      blocks.push_back(b);
    }
    if (blocks.empty() || blocks.back().hi + 1 < n)
    {
      Block b = {blocks.empty() ? 0 : blocks.back().hi + 1, n - 1, bitset<maxN>(0)};
      for (int i = b.lo; i < n; i++)
        if (!b.numbers[c[i] - 1])
          b.numbers.flip(c[i] -1 );
      blocks.push_back(b);
    }

    while (q--)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;

      bitset<maxN> ans;
      for (int i = l; i <= r; i++)
      {
        if (i % blockSize == 0)
          while (i + blockSize <= r)
          {
            ans |= blocks[i / blockSize].numbers;
            i += blockSize;
          }
        if (!ans[c[i] - 1])
          ans.flip(c[i] - 1);
      }
      printf("%ld\n", ans.count());
    }
  }
  return 0;
}