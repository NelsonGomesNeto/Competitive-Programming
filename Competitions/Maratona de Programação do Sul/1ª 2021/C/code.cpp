#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

  // precalc:

  // 1 - 2
  // 2 - 7
  // 3 - 5
  // 4 - 30
  // 5 - 169
  // 6 - 441
  // 7 - 1872
  // 8 - 7632
  // 9 - 1740
  // 10 - 93313
  // 11 - 459901
  // 12 - 1358657
  // 13 - 2504881
  // 14 - 13482720
  // 15 - 25779600
  // 16 - 68468401
  // 17 - 610346880
  // 18 - 1271932200
  // 19 - 327280800

  // lli ans = 0;
  // for (ans = 0; ; ans++)
  // {
  //   hehe.clear();
  //   for (int i = 1; i <= 2*n; i++)
  //     hehe.push_back(i);

  //   bool fuck = false;
  //   int prv = 0;
  //   while (hehe.size() > n)
  //   {
  //     auto it = hehe.begin() + ((prv + ans) % hehe.size());
  //     prv = it - hehe.begin();
  //     DEBUG printf("\t%d %lld %d\n", n, ans, *it);
  //     if (*it <= n)
  //     {
  //       fuck = true;
  //       break;
  //     }
  //     hehe.erase(it);
  //   }
  //   if (!fuck) break;
  // }

int main()
{
  vector<lli> precalc = {2, 7, 5, 30, 169, 441, 1872, 7632, 1740, 93313, 459901, 1358657, 2504881, 13482720, 25779600, 68468401, 610346880, 1271932200, 327280800};
  int n;
  while (~scanf("%d", &n))
    printf("%lld\n", precalc[n - 1]);
  return 0;
}