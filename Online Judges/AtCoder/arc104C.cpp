#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
once A_i and B_i are defined:
j in (A_i, B_i):
  if j == A (going in):
    B = j + (C + 1)
  if j == B (going out):
    B = j - (C + 1)
*/

const int maxN = 1e2; int n;
int a[maxN], b[maxN];
int type[2*maxN]; // 0 - missing, 1 - A, 2 - B

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(type, 0, sizeof(type));

    for (int i = 0; i < n; i++)
    {
      scanf("%d %d", &a[i], &b[i]);
      if (a[i] > 0) a[i]--;
      if (b[i] > 0) b[i]--;
      if (a[i] >= 0) type[a[i]] = 1;
      if (b[i] >= 0) type[b[i]] = 2;
    }

    bool can = false;
    for (int i = 0; i < n; i++)
      for (int ka = 0; ka < 2*n; ka++)
        for (int kb = ka + 1; kb < 2*n; kb++)
        {
          int auxa = a[i];
          int auxtypeka = type[ka];
          if (a[i] == -1 && type[ka] == 0) a[i] = ka, type[ka] = 1;
          int auxb = b[i];
          int auxtypekb = type[kb];
          if (b[i] == -1 && type[kb] == 0) a[i] = kb, type[kb] = 2;

          int c = b[i] - a[i] - 1;
          bool now = true;
          for (int j = 0; j < n; j++)
            if (a[j] < a[i] && )
          for (int j = a[i] + 1; j < b[i]; j++)
            if (!(type[j] == 1 && j + c + 1 < 2*n && type[j + c + 1] == 2)
              || !(type[j] == 2 && j - (c + 1) >= 0 && type[j - (c + 1)] == 1)
              || !(type[j] == 0))
              now = false;
          can |= now;

          a[i] = auxa, type[ka] = auxtypeka;
          b[i] = auxb, type[kb] = auxtypekb;
        }

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
