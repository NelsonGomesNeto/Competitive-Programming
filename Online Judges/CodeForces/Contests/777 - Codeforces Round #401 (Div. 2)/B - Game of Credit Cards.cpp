#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int n;

void read(int a[])
{
  for (int i = 0; i < n; i ++) scanf("%01d", &a[i]);
}

int evaluate(int sherlock[], int moriaty[], int start, int kind)
{
  int hit = 0;
  for (int k = 0, i = start; k < n; k ++, i ++)
  {
    i %= n;
    if (!kind && sherlock[k] < moriaty[i])
      hit ++;
    else if (kind && moriaty[i] < sherlock[k])
      hit ++;
    DEBUG printf("%d %d %d %d\n", kind, hit, sherlock[k], moriaty[i]);
  } DEBUG printf("\n");

  return(hit);
}

int evaluateRange(int sherlock[], int moriaty[], int lo, int hi, int kind)
{
  int best = kind * 999999;
  for (int i = lo; i <= hi; i ++)
  {
    int e = evaluate(sherlock, moriaty, i, kind);
    if (kind && e < best)
      best = e;
    if (!kind && e > best)
      best = e;
  }
  return(best);
}

int main()
{
  scanf("%d", &n);
  int sherlock[n], moriaty[n];
  read(sherlock); read(moriaty);
  sort(sherlock, sherlock+n); sort(moriaty, moriaty+n);

  int minimum = n - 1;
  for (int i = n - 1; i >= 0; i --)
    if (moriaty[minimum] >= sherlock[i]) minimum --;

  minimum ++;
  int maximum = 0;
  for (int i = 0; i < n; i ++)
    if (moriaty[i] > sherlock[maximum]) maximum ++;

  printf("%d\n%d\n", minimum, maximum);
  return(0);
}
