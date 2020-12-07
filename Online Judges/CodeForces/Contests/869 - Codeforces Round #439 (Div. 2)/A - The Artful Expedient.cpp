#include <stdio.h>
#include <string.h>

int main()
{
  int size; scanf("%d", &size);
  int ko[size], ka[size], digits[2000001], i;
  memset(digits, 0, sizeof(digits));
  for (i = 0; i < size; i ++)
  {
    scanf("%d", &ko[i]);
    digits[ko[i]] = 1;
  }

  for (i = 0; i < size; i ++)
  {
    scanf("%d", &ka[i]);
    digits[ka[i]] = 1;
  }


  int pairs = 0, j;
  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      pairs += digits[ko[i] ^ ko[j]];
  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      pairs += digits[ka[i] ^ ka[j]];

  printf("%s\n", pairs & 1 ? "Koyomi" : "Karen");

  return(0);
}