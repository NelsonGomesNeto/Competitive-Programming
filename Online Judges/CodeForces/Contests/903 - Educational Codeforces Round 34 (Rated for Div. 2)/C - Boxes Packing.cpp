#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int box[n], room[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &box[i]);
    room[i] = box[i];
  }
  sort(box, box + n);
  sort(room, room + n);

  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
      if (box[i] < room[j])
      {
        room[j] = box[i];
        box[i] = 1e9 + 1;
        break;
      }

  int visible = 0;
  for (int i = 0; i < n; i ++)
  {
    //printf("(%d, %d)\n", box[i], room[i]);
    if (box[i] != 1e9 + 1) visible ++;
  }

  printf("%d\n", visible);

  return(0);
}