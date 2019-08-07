#include <bits/stdc++.h>
using namespace std;

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    int before[n], after[n], map[n], a;
    for (int i = 0; i < n; i ++)
      scanf("%d", &before[i]);
    for (int i = 0; i < n; i ++)
      scanf("%d", &after[i]);

    int pass = 0;
    for (int k = 0; k < n; k ++)
      if (after[k] != before[k])
        for (int i = k; i < n; i ++)
          if (before[i] == after[k])
            for (int j = i; j > k; j --)
            {
              swap(&before[j], &before[j - 1]);
              pass ++;
            }

    printf("%d\n", pass);
  }
  return(0);
}