#include <bits/stdc++.h>
#define lli long long int

lli convert36to10(char s[])
{
  lli size = strlen(s), pot = 1, total = 0;
  for (int i = size - 1; i >= 0; i --)
  {
    total += pot * (s[i] >= '0' && s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10);
    pot *= 36;
  }
  return(total);
}

void convert10to36(char dest[], int i, lli num)
{
  dest[i] = '\0';
  if (num == 0) return;
  dest[i] = (num % 36) < 10 ? (num % 36) + '0' : ((num % 36) - 10) + 'A';
  convert10to36(dest, i + 1, num / 36);
}

void revert(char num[])
{
  int size = strlen(num); char aux;
  for (int i = 0, j = size - 1; i < size / 2; i ++, j --)
  {
    aux = num[i];
    num[i] = num[j];
    num[j] = aux;
  }
}

int main()
{
  char a[100], b[100];
  while (scanf("%s %s", a, b) && !(!strcmp(a, "0") && !strcmp(b, "0")))
  {
    getchar();
    lli sum = convert36to10(a) + convert36to10(b);
    //printf("%lld %lld\n", convert36to10(a), convert36to10(b));
    char num[100]; convert10to36(num, 0, sum); revert(num);
    printf("%s\n", num);
  }

  return(0);
}