#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 1e6; int q;
char ss[maxS + 1];
vector<int> a;
vector<int> acc[26];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf(" %s", ss);
    a.clear();
    for (int i = 0; ss[i]; ++i)
      a.push_back(ss[i] - 'a');
    for (int i = 0; i < 26; ++i)
    {
      acc[i].clear();
      acc[i].resize(a.size() + 1);
    }

    for (int j = 0; j < 26; ++j)
      for (int i = 0; i < a.size(); ++i)
        acc[j][i + 1] = (a[i] == j) + acc[j][i];

    scanf("%d", &q);
    int ans = 0;
    for (int qq = 1; qq <= q; ++qq)
    {
      int l, r; scanf("%d %d", &l, &r); --l, --r;
      if (r - l + 1 <= 2)
      {
        ans += (r - l + 1) & 1;
        continue;
      }

      bool can = false;
      bool shouldSwap = false;
      for (int mid : {(l + r - 2) >> 1, (l + r) >> 1})
      {
        DEBUG printf("\t\t%d\n", mid);
        int onesDelta = 0;
        for (int j = 0; j < 26 && onesDelta <= 1; ++j)
        {
          int leftCount = acc[j][mid + 1] - acc[j][l];
          int rightCount = acc[j][r + 1] - acc[j][mid + 1];
          if (shouldSwap) swap(leftCount, rightCount);
          int delta = rightCount - leftCount;

          if (delta == 1)
            ++onesDelta;
          else if (delta > 1 || delta < 0)
            onesDelta = 2;

          DEBUG {
            if (leftCount || rightCount)
              printf("\t\t%d %c - %d %d\n", mid, 'a' + j, leftCount, rightCount);
          }
        }
        can |= onesDelta == 1;
        shouldSwap = true;
      }
      DEBUG printf("\t%d %d - %d | %s\n", l, r, can, string(ss).substr(l, r - l + 1).c_str());
      ans += can;
    }

    printf("Case #%d: %d\n", testCase, ans);
  }
  return 0;
}
