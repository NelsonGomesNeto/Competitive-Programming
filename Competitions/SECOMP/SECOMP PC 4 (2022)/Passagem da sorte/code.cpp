#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int number;
vector<int> digits;

int main()
{
  while (~scanf("%d", &number))
  {
    digits.clear();
    int aux = number;
    for (int i = 0; i < 6; ++i)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }
    reverse(digits.begin(), digits.end());

    bool win = (digits[0] + digits[1] + digits[2]) % 7 == 0 && (digits[3] + digits[4] + digits[5]) % 2 == 0;
    printf("%s\n", win ? "YES" : "NO");
  }
  return 0;
}
