#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int merge(int array[], int lo, int mid, int hi)
{
  int copy[hi - lo + 1], i = lo, j = mid + 1, at = 0, changes = 0;
  while (i <= mid || j <= hi)
  {
    if (i == mid + 1) copy[at ++] = array[j ++];
    else if (j == hi + 1) copy[at ++] = array[i ++];
    else if (array[i] > array[j])
    {
      copy[at ++] = array[j ++]; changes += (mid - i + 1);
    }
    else copy[at ++] = array[i ++];
  }
  for (i = 0; i <= hi - lo; i ++)
    array[lo + i] = copy[i];
  return(changes);
}

int mergeSort(int array[], int lo, int hi)
{
  if (lo >= hi) return(0);
  int changes = 0, mid = (lo + hi) / 2;
  changes += mergeSort(array, lo, mid);
  changes += mergeSort(array, mid + 1, hi);
  changes += merge(array, lo, mid, hi);
  return(changes);
}

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}
// 5 6 0 6 10 15
int bucket(int array[], int n)
{
  int changes = 0, dec = 0;
  for (int i = 0; i < n; i ++)
    if (array[i] != i + 1)
    {
      changes += 2*(array[i] - array[array[i] - 1]) - 1;
      swap(&array[i], &array[array[i] - 1]);
      i --;
      //2*(max(array[i], array[array[i] - 1]) - min(array[array[i] - 1], array[i])) - 1;
    }
  return(changes);
}

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int array[n];
    for (int i = 0; i < n; i ++)
      scanf("%d", &array[i]);

    int changes = bucket(array, n);
    DEBUG printf("%d %d\n", changes, mergeSort(array, 0, n - 1));
    printf("%s\n", (changes & 1) ? "Marcelo" : "Carlos");
  }
  return(0);
}