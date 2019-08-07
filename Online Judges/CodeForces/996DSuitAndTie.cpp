#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int paired(int a[], vector<int> mapping[], int n)
{
  for (int i = 0; i < n / 2; i ++) mapping[i].clear();
  int can = 1;
  for (int i = 0; i < n - 1; i += 2)
  {
    if (a[i] != a[i + 1]) can = 0;
    mapping[a[i]].push_back(i);
    mapping[a[i + 1]].push_back(i + 1);
  }
  return(can);
}

int main()
{
  int n; scanf("%d", &n); n = 2 * n;
  int a[n]; for (int i = 0; i < n; i ++) { scanf("%d", &a[i]); a[i] --; }
  vector<int> mapping[n / 2];

  paired(a, mapping, n);
  int steps = 0;
  for (int i = 0; i < n; i ++)
  {
    DEBUG printf("\n%d - %d %d\n", i, mapping[a[i]][0], mapping[a[i]][1]);
    DEBUG for (int j = 0; j < n; j ++) printf("%d%c", a[j], j < n - 1 ? ' ' : '\n');
    if (mapping[a[i]][1] != mapping[a[i]][0] + 1)
    {
      steps += mapping[a[i]][1] - mapping[a[i]][0] - 1;
      for (int k = mapping[a[i]][1]; k > mapping[a[i]][0] + 1; k --)
        swap(&a[k], &a[k - 1]);
      paired(a, mapping, n);
    }
  }

  printf("%d\n", steps);

  return(0);
}