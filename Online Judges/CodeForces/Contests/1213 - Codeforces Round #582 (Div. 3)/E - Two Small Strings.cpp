#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  Test all permutation of "abc" (let's call it p):
    for each test, you have two options:
      ans = p + p + ... p
      or
      ans = n*p[0] + n*p[1] + n*p[2]
*/

const int maxN = 1e5; int n;
char s[3*maxN + 1], A[3], B[3];
char ansStr[3*maxN + 1];

bool check()
{
  for (int i = 1; ansStr[i]; i ++)
    if ((A[0] == ansStr[i - 1] && A[1] == ansStr[i]) ||
        (B[0] == ansStr[i - 1] && B[1] == ansStr[i]))
      return false;
  return true;
}

bool valid(char p[])
{
  for (int i = 0, end = 3*n; i < end; i += 3)
    ansStr[i] = p[0], ansStr[i + 1] = p[1], ansStr[i + 2] = p[2];
  if (check()) return true;
  for (int i = 0; i < n; i ++) ansStr[i] = p[0];
  for (int i = n, end = 2*n; i < end; i ++) ansStr[i] = p[1];
  for (int i = 2*n, end = 3*n; i < end; i ++) ansStr[i] = p[2];
  return check();
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(ansStr, '\0', sizeof(ansStr));
    scanf(" %s\n%s", A, B);
    char p[4] = "abc";
    do; while (!valid(p) && next_permutation(p, p+3));
    if (valid(p)) printf("YES\n%s\n", ansStr);
    else printf("NO\n");
  }
  return(0);
}