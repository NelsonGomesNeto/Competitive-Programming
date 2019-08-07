#include <bits/stdc++.h>
using namespace std;
const int maxSize = 1e6;
int a[maxSize], n;
// IT'S VERY IMPORTANT TO KEEP IN MIND THAT:
// USUALLY TERNARY SEARCH IS USED FOR DOUBLE ANSWERS

void printAns(int pos)
{
  for (int i = 0; i < n; i ++) printf(" %4d", a[i]);
  printf("\n         %4d:",pos); for (int i = 0; i < pos; i ++) printf("     ");
  printf("    ^\n");
}

int ternarySearch(int lo, int hi)
{
  if (lo >= hi - 2) return((a[hi] < a[hi - 1] && a[hi] < a[hi - 2]) ? hi : (a[hi - 1] < a[hi - 2] ? hi - 1 : hi - 2));
  int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
  if (a[lo] < a[hi]) return(ternarySearch(lo, midhi));
  if (a[lo] > a[hi]) return(ternarySearch(midlo, hi));
  return(ternarySearch(midlo, midhi));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  printf("ternarySearch:"); printAns(ternarySearch(0, n - 1));
  return(0);
}
