#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, k;
char s[3*maxN + 1];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);
      scanf(" %s", s);
      DEBUG printf("%d %d - %s\n", n, k, s);
      for (int i = n, end = n + (k - n % k); i < end; i++)
        s[i] = '?';

      n += k - n % k;
      s[n] = '\0';

      bool can = true;

      for (int i = 0; i < k; i++)
      {
        int ones = 0, zeros = 0;
        for (int j = i; j < n; j += k)
          ones += s[j] == '1', zeros += s[j] == '0';

        char toSet;
        if (ones != 0 && zeros != 0)
          can = false;
        else if (ones == 0 && zeros == 0)
          toSet = '?';
        else if (ones == 0)
          toSet = '0';
        else
          toSet = '1';

        for (int j = i; j < n; j += k)
          s[j] = toSet;
      }
      int ones = 0, zeros = 0;
      for (int i = 0; i < n; i++)
        ones += s[i] == '1', zeros += s[i] == '0';
      for (int i = 0; i < k; i++)
        if (s[i] == '?')
        {
          for (int j = i; j < n; j += k)
            s[j] = ones < zeros ? '1' : '0';
          if (ones < zeros) ones += n / k;
          else zeros += n / k;
        }

      if (can)
      {
        int o = 0, z = 0;
        for (int i = 0; i < n; i++)
        {
          assert(s[i] != '?');
          o += s[i] == '1', z += s[i] == '0';
          if (i >= k)
            o -= s[i - k] == '1', z -= s[i - k] == '0';

          if (i + 1 >= k && o != z)
            can = false;
        }
      }

      DEBUG printf("\t%s\n", s);

      printf("%s\n", can ? "YES" : "NO");
    }
  }
  return 0;
}
/*
i == i + k
0101
0101

*/