#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that:
    1st: k^123 == k^(100 + 20 + 3) == k^100 * k^20 * k^3
    2nd: k^20 == (k^10)^2
    3rd: (k^(10^i))^10 = k^(10^(i + 1))
    REMEMBER TO APPLY MOD 5 ON EVERY OPERATION

  For each number k in (1, 2, 3, 4) construct from k^(10^0) to k^(10^|n|) (size of number n)
    You can construct using the 3rd observation
  For each number k, and accordingly with the i-th digit of s: (reverse the string, please)
    Use the 2nd observation to fix k^(10^i) to (k^(10^i))^s[i]
  ans = 0
  For each number k, reconstruct the full number:
    Use the 1st observation and multiply all (k^(10^i))^s[i]
    Then add it to the answer:
      ans = (ans + reconstructedNumber) % 5
*/

const int maxN = 1e5; int n;
char s[maxN + 1];
int ans[maxN][5];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);
    reverse(s, s+n);

    for (int j = 1; j <= 4; j ++)
      ans[0][j] = j;
    for (int i = 1; i < n; i ++)
      for (int j = 1; j <= 4; j ++)
        ans[i][j] = (int) pow(ans[i - 1][j], 10) % 5;
    DEBUG
      for (int i = 0; i < n; i ++)
        printf("\t%d %d\n", i, ans[i][2]);
    for (int i = 0; i < n; i ++)
      for (int j = 1; j <= 4; j ++)
        ans[i][j] = (int) pow(ans[i][j], s[i] - '0') % 5;

    int fans = 0;
    for (int j = 1; j <= 4; j ++)
    {
      int cur = 1;
      for (int i = 0; i < n; i ++)
        cur = (cur * ans[i][j]) % 5;
      fans = (fans + cur) % 5;
    }
    printf("%d\n", fans);
  }

  return 0;
}