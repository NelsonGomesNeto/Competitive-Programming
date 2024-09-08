#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
>>> a = [1,6,4,2,3,5,4]
>>> b = [a[0] & aa for aa in a[1:]]
>>> c = [a[0] | aa for aa in a[1:]]
>>> [bb ^ cc for bb, cc in zip(b, c)]
[7, 5, 3, 2, 4, 5]
>>> sorted([bb ^ cc for bb, cc in zip(b, c)])
[2, 3, 4, 5, 5, 7]
>>> sorted([1 ^ bb ^ cc for bb, cc in zip(b, c)])
[2, 3, 4, 4, 5, 6]
*/

const int maxN = 1e4; int n, k;
lli arr[maxN];
lli curr[maxN];
lli b[maxN], c[maxN];
lli bc[maxN];
lli buntie, cuntie;

const string mode[2] = {"and", "or"};
lli query(bool m, int i, int j)
{
  printf("%s %d %d\n", mode[m].c_str(), i + 1, j + 1); fflush(stdout);
  lli res; scanf("%lld", &res);
  return res;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    // 2*n - 2 queries
    for (int i = 1; i < n; i++) b[i] = query(0, 0, i);
    for (int i = 1; i < n; i++) c[i] = query(1, 0, i);
    buntie = query(0, 1, 2);
    cuntie = query(1, 1, 2);
    for (int i = 1; i < n; i++) bc[i] = b[i] ^ c[i];

    lli first = 0;
    for (lli bit = 0; bit < 32; bit++)
    {
      //        and or
      // 0 0 ->   0  0
      // 0 1 ->   0  1
      // 1 0 ->   0  1
      // 1 1 ->   1  1

      // 0
      for (int i = 1; i < n; i++)
        curr[i] = bc[i] ^ first;

      bool valid = true;
      for (int i = 1; i < n; i++)
      {
        lli bb = first & curr[i];
        lli cc = first | curr[i];
        lli ub = curr[1] & curr[2];
        lli uc = curr[1] | curr[2];
        DEBUG
          if (bit <= 3)
          {
            printf("DEBUG-%lld: %lld %lld %lld\n", bit, first, bb, cc);
            fflush(stdout);
          }
        if (!(((bb >> bit) & 1LL) == ((b[i] >> bit) & 1LL) &&
              ((cc >> bit) & 1LL) == ((c[i] >> bit) & 1LL) &&
              ((ub >> bit) & 1LL) == ((buntie >> bit) & 1LL) &&
              ((uc >> bit) & 1LL) == ((cuntie >> bit) & 1LL) ))
        {
          valid = false;
        }
      }
      DEBUG
        if (bit <= 3)
        {
          printf("DEBUG-%lld: %d\n", bit, valid);
          fflush(stdout);
        }

      if (!valid)
        first |= 1LL << bit;
    }

    curr[0] = arr[0] = first;
    for (int i = 1; i < n; i++)
      curr[i] = arr[i] = bc[i] ^ arr[0];

    sort(arr, arr+n);

    DEBUG {
      printf("DEBUG-arr:");
      for (int i = 0; i < n; i++)
        printf(" %lld", curr[i]);
      printf("\n");

      printf("DEBUG---b:");
      for (int i = 0; i < n; i++)
        printf(" %lld", b[i]);
      printf("\n");

      printf("DEBUG---c:");
      for (int i = 0; i < n; i++)
        printf(" %lld", c[i]);
      printf("\n");

      printf("DEBUG--bc:");
      for (int i = 0; i < n; i++)
        printf(" %lld", bc[i]);
      printf("\n");
      fflush(stdout);
    }
    printf("finish %lld\n", arr[k - 1]); fflush(stdout);
  }

  return 0;
}
