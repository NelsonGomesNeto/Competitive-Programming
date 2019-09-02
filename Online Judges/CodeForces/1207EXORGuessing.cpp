#include <bits/stdc++.h>
 
int main()
{
  int ans, q;
 
  printf("?");
  for (int i = 1; i <= 100; i ++)
    printf(" %d", i);
  printf("\n"); fflush(stdout);
  
  scanf("%d", &q);
  ans = q & ~((1 << 7) - 1);
 
  printf("?");
  for (int i = 1; i <= 100; i ++)
    printf(" %d", i << 7);
  printf("\n"); fflush(stdout);
 
  scanf("%d", &q);
  ans |= q & ((1 << 7) - 1);
  
  printf("! %d\n", ans); fflush(stdout);
 
  return 0;
}