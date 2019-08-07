#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 24; int n;
int a[maxN], b[maxN], aa[maxN], bb[maxN];

void read(int arr[])
{
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &arr[i]);
    arr[i] --;
  }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    read(a); read(b);

    for (int i = 0; i < n; i ++)
      aa[a[i]] = i;
    for (int i = 0; i < n; i ++)
      bb[i] = aa[b[i]];
    // for (int i = 0; i < n; i ++)
      // printf("%d%c", bb[i], i < n - 1 ? ' ' : '\n');

    int inv = 0;
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
        inv += bb[i] > bb[j];
    printf("%d\n", inv);
  }
  return(0);
}