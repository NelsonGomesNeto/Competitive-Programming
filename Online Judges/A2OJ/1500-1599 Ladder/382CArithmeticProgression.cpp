#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  sort(a, a+n);
  if (n == 1) printf("-1\n");
  else if (n == 2)
  {
    int q = a[1] - a[0];
    if (q == 0) printf("1\n%d\n", a[0]);
    else if (q & 1) printf("2\n%d %d\n", a[0] - q, a[1] + q);
    else printf("3\n%d %d %d\n", a[0] - q, a[0] + (q >> 1), a[1] + q);
  }
  else
  {
    map<int, int> ap;
    for (int i = 0; i < n - 1; i ++)
      if (!ap.count(a[i + 1] - a[i])) ap[a[i + 1] - a[i]] = 1;
      else ap[a[i + 1] - a[i]] ++;

    int q = a[1] - a[0];
    if (ap.size() == 1 && q == 0) printf("1\n%d\n", a[0]);
    else if (ap.size() == 1) printf("2\n%d %d\n", a[0] - q, a[n - 1] + q);
    else if (ap.size() == 2)
    {
      int q1 = ap.begin()->first, q2 = (++ap.begin())->first;
      if (ap[q1] > 1 && ap[q2] > 1) printf("0\n");
      else
      {
        if (ap[q1] == 1 && !(q1 & 1) && (q1 >> 1) == q2)
        {
          int number = 0;
          for (int i = 0; i < n - 1; i ++)
            if (a[i + 1] - a[i] == q1)
              number = a[i] + q2;
          printf("1\n%d\n", number);
        }
        else if (ap[q2] == 1 && !(q2 & 1) && (q2 >> 1) == q1)
        {
          int number = 0;
          for (int i = 0; i < n - 1; i ++)
            if (a[i + 1] - a[i] == q2)
              number = a[i] + q1;
          printf("1\n%d\n", number);
        }
        else printf("0\n");
      }
    }
    else printf("0\n");
  }
  return(0);
}