#include <stdio.h>
#include <vector>
#include <algorithm>
// TUDO ERRADO, ESSA POARR NÃO É COM BUSCA TERNÁRIA T-T
using namespace std;

int maxi;

int cut(int p[], int h, int size)
{
  int cutted = 1, i;
  for (i = 0; i < size;)
  {
    while (i < size && p[i] <= h) i ++;
    while (i < size && p[i] > h) i ++;
    cutted ++;
  }
  if (p[i - 1] < h)
    cutted --;

  if (cutted > maxi)
    maxi = cutted;

  return(cutted);
}

int ma(int a, int b)
{
  return(a > b ? a : b);
}

int ternarySearch(int a[], int p[], int start, int end, int size)
{
  //printf("%d %d - ", start, end);
  if (end - start < 1)
    return(a[(end + start) / 2]);

  int left = start + (end - start) / 3;
  int right = end - (end - start) / 3;

  int cutL = cut(p, a[start], size);
  int cutR = cut(p, a[end], size);
  int i;
  for (i = 1; i < 11; i ++)
  {
    if (start - i >= 0)
      cutL = ma(cutL, cut(p, a[start - i], size));
    if (start + i < size)
      cutL = max(cutL, cut(p, a[start + i], size));
    if (end - i >= 0)
      cutR = ma(cutR, cut(p, a[end - i], size));
    if (end + i < size)
      cutR = ma(cutR, cut(p, a[end + i], size));
  }

  if (cutL <= cutR)
    return(ternarySearch(a, p, left + 1, end, size));
  else //if (cutL > cutR)
    return(ternarySearch(a, p, start, right - 1, size));
  //else
    //return(ternarySearch(a, p, left + 1, right - 1, size));
}

int main()
{
  int papers; scanf("%d", &papers);
  int p[papers], a[papers], i;
  for (i = 0; i < papers; i ++)
  {
    scanf("%d", &p[i]);
    a[i] = p[i];
  }

  sort(a, a + papers);

  maxi = 0;
  for (i = 0; i < papers; i ++)
  {
    //printf("i: %d cut: %d a: %d p: %d\n", i, cut(p, a[i], papers), a[i], p[i]);
  }
  //77
  ternarySearch(a, p, 0, papers - 1, papers);

  printf("%d\n", maxi);

  return(0);
}
