#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN], b[maxN];

void read(int arr[], int sz)
{
  for (int i = 0; i < sz; i ++)
    scanf("%d", &arr[i]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    read(a, n);
    read(b, n);

    bool can = true; int diff = 0;
    for (int i = 0; i < n; i ++)
      if (a[i] != b[i])
      {
        int j = i;
        int v = b[i] - a[i];
        if (v < 0) can = false;
        while (j + 1 < n && a[j + 1] != b[j + 1])
        {
          j ++;
          if (b[j] - a[j] != v)
            can = false;
        }
        i = j;
        diff ++;
      }
    if (diff > 1) can = false;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
