#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
lli a[maxN];

struct Operation
{
  int i, j; lli x;
  void apply()
  {
    a[i] -= (i + 1) * x;
    a[j] += (i + 1) * x;
  }
};

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      lli sum = 0;
      for (int i = 0; i < n; i++)
      {
        scanf("%lld", &a[i]);
        sum += a[i];
      }

      if (sum % n != 0) printf("-1\n");
      else
      {
        lli target = sum / n;
        vector<Operation> ans;
        for (int k = 0; k < 2; k++)
          for (int i = 1; i < n; i++)
          {
            if (a[i] % (i + 1) != 0)
            {
              lli delta = (i + 1) - (a[i] % (i + 1));
              if (delta <= a[0])
              {
                Operation safe = Operation{0, i, delta};
                safe.apply();
                ans.push_back(safe);
              }
            }

            lli x = a[i] / (i + 1);
            if (x > 0)
            {
              Operation op = Operation{i, 0, x};
              op.apply();
              ans.push_back(op);
            }
          }

        for (int i = 1; i < n; i++)
        {
          Operation last = Operation{0, i, target};
          last.apply();
          ans.push_back(last);
        }

        DEBUG {
          printf("final %d: ", (int)ans.size());
          for (int i = 0; i < n; i++)
            printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
        }

        bool can = ans.size() <= 3*n;
        for (int i = 0; i < n; i++) can &= a[i] == target;
        if (!can) printf("-1\n");
        else
        {
          printf("%d\n", (int)ans.size());
          for (auto &op: ans)
            printf("%d %d %lld\n", op.i + 1, op.j + 1, op.x);
        }
      }
    }
  return 0;
}