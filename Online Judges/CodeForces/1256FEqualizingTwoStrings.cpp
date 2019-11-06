#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
#define ldouble long double

/* Tutorial:
  There are two easy cases:
    Both strings doesn't have the same character count: NO
    Both strings have any character twice or more (cnt[chr] > 1): YES
      Also notice that this will ALWAYS happen if n > 26, since the alphabet
      has 26 letters.
      That is true because if we sort s (the changes in t won't matter), we can
      also sort t afterwards, since we can ALWAYS swap the character in which
      cnt[chr] > 1 and that won't unsort s.
  Now for the hard case, suppose we wanted to make both string sorted. Since
  every change in string s need to be reflected to string t.
  If to sort s and t, you needed odd swaps in s and odd swaps in t: YES
    Suppose we needed 3 swaps in s and 5 swaps in t. We first sort s,
    and t will need 2 more swaps. Since we need an even number of swaps, we
    can swap the same pair in s that even number of times.
  If to sort s and t, you needed even swaps in s and even swaps in t: YES
    Same above explanation
*/

const int maxN = 2e5; int n;
char s[2][maxN + 1];
int cnt[2][256];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %s %s", &n, s[0], s[1]);
    memset(cnt, 0, sizeof(cnt));
    for (int j = 0; j < 2; j ++)
      for (int i = 0; i < n; i ++)
        cnt[j][s[j][i]] ++;

    bool can = true, easy = false;
    for (int i = 0; i < 256; i ++)
    {
      if (cnt[0][i] != cnt[1][i])
        can = false;
      if (cnt[0][i] > 1)
        easy = true;
    }
    if (can)
    {
      if (easy)
        printf("YES\n");
      else
      {
        int inv[2] = {0, 0};
        for (int k = 0; k < 2; k ++)
          for (int i = 0; i < n; i ++)
            for (int j = i + 1; j < n; j ++)
              inv[k] += s[k][i] > s[k][j];
        printf("%s\n", (inv[0] & 1) == (inv[1] & 1) ? "YES" : "NO");
      }
    }
    else
      printf("NO\n");
  }
  return 0;
}
