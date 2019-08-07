#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

lli calculate(lli a, lli b, char e)
{
  if (e == '+') return(a + b);
  return(a * b);
}

lli solve(int maximum, deque<lli> number, deque<char> expression)
{
  while (expression.size() > 1)
  {
    DEBUG for (int i = 0; i < number.size(); i ++) printf("%lld%c", number[i], expression[i]); DEBUG printf("\n");
    char left = expression[0], right = expression[1];
    if (left == right || (!maximum && right == '+') || (maximum && right == '*'))
      number[1] = calculate(number[0], number[1], left);
    else
    {
      number[2] = calculate(number[1], number[2], right);
      number[1] = number[0];
      expression[1] = expression[0];
    }
    number.pop_front();
    expression.pop_front();
  }
  return(calculate(number[0], number[1], expression[0]));
}

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    deque<lli> number; deque<char> e; lli num; char end;
    while (scanf("%lld%c", &num, &end) && end != '\n')
    {
      number.push_back(num); e.push_back(end);
    } number.push_back(num);

    lli minimum = solve(0, number, e);
    lli maximum = solve(1, number, e);
    printf("The maximum and minimum are %lld and %lld.\n", maximum, minimum);
  }
  return(0);
}