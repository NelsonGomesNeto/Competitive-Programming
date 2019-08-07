#include <bits/stdc++.h>
#define lli long long int
using namespace std;

// Maximum value for the equation will be: 9*9 = 81
vector<lli> answers;
lli sumDigits(lli number)
{
  lli sum = 0;
  while (number)
  {
    sum += number % 10;
    number /= 10;
  }
  return(sum);
}

int main()
{
  lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
  for (lli x = 1; x <= 81; x ++)
  {
    lli value = b * pow(x, a) + c;
    if (value > 0 && value < 1e9 && sumDigits(value) == x) answers.push_back(value);
  }
  printf("%d\n", (int) answers.size());
  for (int i = 0; i < answers.size(); i ++) printf("%lld%c", answers[i], i < answers.size() - 1 ? ' ' : '\n');
  return(0);
}