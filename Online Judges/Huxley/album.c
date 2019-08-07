#include <stdio.h>

struct retangulo
{
  int x, y;
};

int max(int a, int b)
{
  return(a > b ? a : b);
}

int main()
{
  struct retangulo pag;
  struct retangulo pic[2];
  scanf("%d %d", &pag.x, &pag.y);
  scanf("%d %d", &pic[0].x, &pic[0].y);
  scanf("%d %d", &pic[1].x, &pic[1].y);
  if ((pic[0].x + pic[1].x <= pag.x
    && max(pic[0].y, pic[1].y) <= pag.y)
    ||
      (pic[0].x + pic[1].x <= pag.y
    && max(pic[0].y, pic[1].y) <= pag.x)
    ||
      (pic[0].y + pic[1].y <= pag.x
    && max(pic[0].x, pic[1].x) <= pag.y)
    ||
      (pic[0].y + pic[1].y <= pag.y
    && max(pic[0].x, pic[1].x) <= pag.x)
    ||
      (pic[0].x + pic[1].y <= pag.x
    && max(pic[0].y, pic[1].x) <= pag.y)
    ||
      (pic[0].x + pic[1].y <= pag.y
    && max(pic[0].y, pic[1].x) <= pag.x)
    ||
      (pic[0].y + pic[1].x <= pag.x
    && max(pic[0].x, pic[1].y) <= pag.y)
    ||
      (pic[0].y + pic[1].x <= pag.y
    && max(pic[0].x, pic[1].y) <= pag.x))
  {
    printf("S\n");
  }
  else
  {
    printf("N\n");
  }
  return(0);
}
