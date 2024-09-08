#include <bits/stdc++.h>
using namespace std;

int main()
{
  int num;
  while (scanf("%d", &num) != EOF)
  {
    /*int x = 0;
    /*for (i = 0; i < 4; i ++)
    {
      x = (x << 8) | ((num >> (8 * i)) & 255);
    }*/
    int i;
    bitset<32> a (num);
    string A, B, C, D;
    for (i = 31; i >= 0; i --)
    {
      if (i < 8)
      {
        A += (a[i] == 1 ? '1' : '0');
      }
      else if (i < 16)
      {
        B += (a[i] == 1 ? '1' : '0');
      }
      else if (i < 24)
      {
        C += (a[i] == 1 ? '1' : '0');
      }
      else
      {
        D += (a[i] == 1 ? '1' : '0');
      }
    }
    string convert = A + B + C + D;
    bitset<32> x (convert);
    printf("%d converts to ", num);
    cout << (int) x.to_ulong() << endl;
  }
  return(0);
}
