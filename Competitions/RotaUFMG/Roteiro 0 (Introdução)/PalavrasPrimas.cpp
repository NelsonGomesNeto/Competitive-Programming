#include <bits/stdc++.h>

int main()
{
  char word[100];
  while (scanf("%s", word) != EOF)
  {
    getchar();
    int sum = 0;
    for (int i = 0; word[i]; i ++)
      if (word[i] >= 'a' && word[i] <= 'z')
        sum += word[i] - 'a' + 1;
      else
        sum += word[i] - 'A' + 27;

    int prime = 1;
    for (int i = 2; i <= sqrt(sum); i ++)
      if (sum % i == 0)
        prime = 0;

    if (prime)
      printf("It is a prime word.\n");
    else
      printf("It is not a prime word.\n");
  }
  return(0);
}