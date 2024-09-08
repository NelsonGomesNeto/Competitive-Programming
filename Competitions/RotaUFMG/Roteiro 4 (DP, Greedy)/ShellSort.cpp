#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d\n", &n);
    string un[n], so[n];
    for (int i = 0; i < n; i ++)
      getline(cin, un[i]);
    for (int i = 0; i < n; i ++)
      getline(cin, so[i]);

    set<string> toChange; int q = 0;
    for (int i = n - 1, j = n - 1; i >= q; i --, j --)
    {
      //if (j >= 0) cout << so[i] << " | " << un[j] << endl;
      if (j < 0 || so[i] != un[j])
      {
        if (j >= 0) q ++;
        if (j >= 0) toChange.insert(un[j]);
        i ++;
        //for (j = n - 1 - q; j >= 0; j --)
          //if (so[i] == un[j]) break;
      }
    }

    for (int i = n - 1; i >= 0; i --)
      if (toChange.count(so[i]))
        cout << so[i] << endl;
    printf("\n");
  }
  return(0);
}