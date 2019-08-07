#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char A[260], B[260]; int feito, fimA, fimB;

void bt(int a[], int i)
{
  if (B[i] == '\0')
  {
    int k;
    feito = 1;
    for (k = 0; B[k + 1] != '\0'; k ++)
    {
      printf("%d ", a[k] + 1);
    } printf("%d\n", a[k] + 1);
    return;
  }
  int j;
  j = i > 0 ? a[i - 1] : i;
  for (; A[j] != '\0'; j ++)
  {
    if (A[j] == B[i] && (i == 0 || (i > 0 && a[i - 1] < j)))
    {
      a[i] = j;
      bt(a, i + 1);
    }
  }
}

int main()
{
  scanf("%[^\n]", A);
  getchar();
  scanf("%[^\n]", B);
  int ans[260];
  //fimA = strlen(A);
  //fimB = strlen(B);
  feito = 0;
  bt(ans, 0);
  if (feito == 0)
  {
    printf("-1\n");
  }
  return(0);
}
