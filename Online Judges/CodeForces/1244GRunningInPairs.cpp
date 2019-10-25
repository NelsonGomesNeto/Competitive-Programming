#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1; int n;
int a[maxN], b[maxN]; lli k;

void printArray(int arr[], int sz)
{
  for (int i = 1; i <= sz; i ++)
    printf("%d%c", arr[i], i < sz ? ' ' : '\n');
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    lli sum = 0;
    for (int i = 1; i <= n; i ++) sum += a[i] = b[i] = i;
    // printf("\t%lld\n", sum);
    for (int i = 1, j = n; sum < k && i < j; i ++)
      if (sum + (j - i) <= k)
      {
        swap(b[i], b[j]), sum += j - i;
        j --;
      }
    if (sum > k) printf("-1\n");
    else
    {
      printf("%lld\n", sum);
      printArray(a, n);
      printArray(b, n);
    }
  }
  return 0;
}