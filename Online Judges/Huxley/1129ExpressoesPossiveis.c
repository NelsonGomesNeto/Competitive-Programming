#include <stdio.h>
#include <string.h>
#define lli long long int
#define DEBUG if(0)
char expression[5] = "+-*e";

void printResult(char n[], char selected[])
{
  int i, j; printf("%c", n[0]);
  for (i = 1, j = 0; n[i]; i ++, j ++)
  {
    if (selected[j] != 'e') printf("%c", selected[j]);
    printf("%c", n[i]);
  }
}

int countNumbers(char selected[])
{
  int i, numbers = 1;
  for (i = 0; selected[i]; i ++) numbers += selected[i] != 'e';
  return(numbers);
}

void getNumbers(char n[], char selected[], lli number[])
{
  int i, j, k; lli newNum = n[0] - '0';
  for (i = 1, j = 0, k = 0; n[i]; i ++, j ++)
  {
    int bug = selected[j] == 'e';
    while (n[i] && selected[j] == 'e')
    {
      newNum = newNum*10 + n[i] - '0';
      i ++; j ++;
    }
    number[k ++] = newNum; newNum = n[i] - '0';
  } number[k] = newNum;
}

lli calculate(lli a, lli b, char oper)
{
  if (oper == '*') return(a * b);
  if (oper == '+') return(a + b);
  return(a - b);
}

lli calculateResult(char n[], char selected[])
{
  int numbers = countNumbers(selected);
  lli number[numbers]; getNumbers(n, selected, number);
  //DEBUG for (int j = 0; j < numbers; j ++) printf("%lld%c", number[j], j < numbers - 1 ? ' ' : '\n');

  char operation[13] = ""; int j, k;
  for (k = 0, j = 0; selected[j]; j ++)
  {
    if (selected[j] == 'e') continue;
    operation[k ++] = selected[j];
  } operation[k] = '\0';

  lli result = 0;
  if (!operation[0])
    result = number[0];
  else if (!operation[1])
    result = calculate(number[0], number[1], operation[0]);
  else
  {
    char prevOp = operation[0]; int missing = 0;
    for (j = 1; operation[j]; j ++)
    {
      if (prevOp != '*' && operation[j] == '*')
      {
        lli aux = number[j] * number[j + 1];
        number[j] = number[j - 1]; number[j + 1] = aux;
        operation[j] = prevOp; prevOp = operation[j];
        operation[j - 1] = 'd';
      }
      else
      {
        number[j] = calculate(number[j - 1], number[j], prevOp);
        prevOp = operation[j];
      }
      if (!operation[j + 1]) missing = 1;
    } result = number[numbers - 1];
    if (prevOp) result = calculate(number[numbers - 2], number[numbers - 1], prevOp);
    DEBUG for (j = 0; j < numbers; j ++) printf(" %lld%c", number[j], j < numbers - 1 ? ' ' : '\n');
  }
  return(result);
}

int isFirst = 1, now = 0; char answer[100000][13];

void tryAll(char n[], char selected[], int i, lli target)
{
  if (!n[i + 1])
  {
    DEBUG { printResult(n, selected); printf("\n"); }

    lli result = calculateResult(n, selected);
    DEBUG printf("%lld\n\n", result);
    if (result == target) strcpy(answer[now ++], selected);
    return;
  }
  int k;
  for (k = 0; k < 4; k ++)
  {
    selected[i] = expression[k];
    tryAll(n, selected, i + 1, target);
  }
}

int main()
{
  char n[13] = ""; lli t; scanf("%s\n%lld", n, &t);
  char selected[13] = "";
  tryAll(n, selected, 0, t);

  printf("["); printResult(n, answer[0]);
  int o; for (o = 1; o < now; o ++)
  {
    printf(", ");
    printResult(n, answer[o]);
  }
  printf("]\n");

  return(0);
}