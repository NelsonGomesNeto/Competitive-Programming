#include <stdio.h>
#include <string.h>
#define DEBUG if(0)

void solve(int p, int t, int n, int s, char stack[], int i, int size, char command[], char string[], char target[])
{
  if (i == size)
  {
    int j;
    for (j = 0; j < size - 1; j ++)
      printf("%c ", command[j]);
    printf("%c\n", command[j]);
  }
  if (t < size / 2)
  {
    command[i] = 'i';
    char prev = stack[s];
    stack[s] = string[p];
    solve(p + 1, t + 1, n, s + 1, stack, i + 1, size, command, string, target);
    stack[s] = prev;
  }
  if (s > 0 && stack[s - 1] == target[n])
  {
    command[i] = 'o';
    solve(p, t, n + 1, s - 1, stack, i + 1, size, command, string, target);
  }
}

int main()
{
  char target[1000], string[1000], command[1000], stack[1000];
  while (scanf("%s\n%s", string, target) != EOF)
  {
    getchar();
    DEBUG printf("%s\n%s\n", target, string);

    int size = strlen(target);
    printf("[\n");
    if (size == strlen(string))
    {
      stack[size] = '\0'; command[size * 2] = '\0';
      solve(0, 0, 0, 0, stack, 0, size * 2, command, string, target);
    }
    printf("]\n");
  }

  return(0);
}