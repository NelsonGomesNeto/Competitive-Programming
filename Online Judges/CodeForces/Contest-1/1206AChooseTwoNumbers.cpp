#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, m;
int a[maxN], b[maxN];

void read(int arr[], int sz)
{
  for (int i = 0; i < sz; i ++)
    scanf("%d", &arr[i]);
}

bool has(int arr[], int target, int sz)
{
  for (int i = 0; i < sz; i ++)
    if (arr[i] == target)
      return(true);
  return(false);
}

int main()
{
  scanf("%d", &n);
  read(a, n);
  scanf("%d", &m);
  read(b, m);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      if (!has(a, a[i] + b[j], n) && !has(b, a[i] + b[j], m))
      {
        printf("%d %d\n", a[i], b[j]);
        return(0);
      }

  return(0);
}
