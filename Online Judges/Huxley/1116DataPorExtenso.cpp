#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char months[12][20] = {"janeiro", "fevereiro", "marco", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
char hundredsPrefix[11][20] = {"", "c", "duz", "trez", "quatroc", "quinh", "seisc", "setec", "oitoc", "novec"};
char tennineteen[10][20] = {"dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};
char tens[10][20] = {"vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"};
char digit[10][20] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"};

void printNumber(int n, bool printAnd = false)
{
  if (n >= 1000)
  {
    if (n >= 2000) printNumber(n / 1000 - 1);
    printf("mil ");
    printNumber(n % 1000, true);
  }
  else if (n >= 100)
  {
    if (printAnd) printf("e ");
    printf("%sento%s", hundredsPrefix[n / 100], n <= 199 ? " " : "s ");
    printNumber(n % 100, true);
  }
  else if (n >= 10)
  {
    if (printAnd) printf("e ");
    if (n <= 19) printf("%s ", tennineteen[n % 10]);
    else
    {
      printf("%s ", tens[n / 10]);
      printNumber(n % 10, true);
    }
  }
  else if (n < 10 && n)
  {
    if (printAnd) printf("e ");
    printf("%s ", digit[n]);
  }
}

void printMonth(int m)
{
  printf("%s", months[m - 1]);
}

int main()
{
  int d, m, a; scanf("%d %d %d", &d, &m, &a);
  if (a >= 1900 && a <= 2100 && m >= 1 && m <= 12)
  {
    printNumber(d);
    printf("de ");
    printMonth(m);
    printf(" de ");
    printNumber(a);
  }
  else printf("data invalida\n");
  return(0);
}