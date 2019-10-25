#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 81; int n;
char s[maxN];

int pi[maxN];
void prefixFunction(char str[], int strSize)
{
  pi[0] = -1;
  for (int i = 0, j = -1; i < strSize;)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++ i] = ++ j;
  }
}
vector<int> kmp(char str[], int strSize, char subStr[], int subStrSize)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < strSize;)
  {
    while (j >= 0 && str[i] != subStr[j]) j = pi[j];
    i ++, j ++;
    if (j == subStrSize)
    {
      occurrences.push_back(i - subStrSize);
      // j = pi[j];
      j = 0;
    }
  }
  return occurrences;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf(" %s", s); n = strlen(s);
    int ans = n;
    for (int i = 1; i <= (n >> 1); i ++)
      if (n % i == 0)
      {
        prefixFunction(s, i);
        if (kmp(s, n, s, i).size() == n / i)
        {
          ans = i;
          break;
        }
      }
    printf("%d\n", ans);
    if (t) printf("\n");
  }
  return 0;
}