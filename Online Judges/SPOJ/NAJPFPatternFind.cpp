#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1; int n, m;
char a[maxN], b[maxN];

int backTable[maxN];
void preProcess(char subStr[], int subStrSize)
{
  backTable[0] = -1;
  for (int i = 0, j = -1; i < subStrSize;)
  {
    while (j >= 0 && subStr[i] != subStr[j]) j = backTable[j];
    backTable[++ i] = ++ j;
  }
}
vector<int> kmp(char str[], int strSize, char subStr[], int subStrSize)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < strSize;)
  {
    while (j >= 0 && str[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    if (j == subStrSize)
    {
      occurrences.push_back(i - subStrSize);
      j = backTable[j];
    }
  }
  return occurrences;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf(" %s %s", a, b);
    n = strlen(a), m = strlen(b);
    preProcess(b, m);
    vector<int> occurrences = kmp(a, n, b, m);
    if (occurrences.empty()) printf("Not Found\n");
    else
    {
      printf("%d\n", (int) occurrences.size());
      for (int i = 0; i < occurrences.size(); i ++)
        printf("%d%c", occurrences[i] + 1, i < occurrences.size() - 1 ? ' ' : '\n');
    }
    if (t) printf("\n");
  }
  return 0;
}