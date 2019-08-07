#include <stdio.h>
#include <string.h>

#define ler() getchar() && scanf("%[^\n]", num)
#define check() (int) strlen(num) == 1 && num[0] == '0'

void traco(int alt)
{
  int print;
  printf(" ");
  for (print = 0; print < alt; print ++)
  {
    printf("-");
  }
  printf(" ");
}

void espacos(int alt)
{
  int print;
  for (print = 0; print < alt; print ++)
  {
    printf(" ");
  }
}

void print0Top(int alt)
{ traco(alt); }
void print0TopMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print0Mid(int alt)
{ printf(" "); espacos(alt); printf(" "); }
void print0BotMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print0Bot(int alt)
{ traco(alt); }

void print1Top(int alt)
{ printf(" "); espacos(alt); printf(" "); }
void print1TopMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print1Mid(int alt)
{ printf(" "); espacos(alt); printf(" "); }
void print1BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print1Bot(int alt)
{ printf(" "); espacos(alt); printf(" "); }

void print2Top(int alt)
{ traco(alt); }
void print2TopMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print2Mid(int alt)
{ traco(alt); }
void print2BotMid(int alt)
{ printf("|"); espacos(alt); printf(" "); }
void print2Bot(int alt)
{ traco(alt); }

void print3Top(int alt)
{ traco(alt); }
void print3TopMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print3Mid(int alt)
{ traco(alt); }
void print3BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print3Bot(int alt)
{ traco(alt); }

void print4Top(int alt)
{ printf(" "); espacos(alt); printf(" "); }
void print4TopMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print4Mid(int alt)
{ traco(alt); }
void print4BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print4Bot(int alt)
{ printf(" "); espacos(alt); printf(" "); }

void print5Top(int alt)
{ traco(alt); }
void print5TopMid(int alt)
{ printf("|"); espacos(alt); printf(" "); }
void print5Mid(int alt)
{ traco(alt); }
void print5BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print5Bot(int alt)
{ traco(alt); }

void print6Top(int alt)
{ traco(alt); }
void print6TopMid(int alt)
{ printf("|"); espacos(alt); printf(" "); }
void print6Mid(int alt)
{ traco(alt); }
void print6BotMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print6Bot(int alt)
{ traco(alt); }

void print7Top(int alt)
{ traco(alt); }
void print7TopMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print7Mid(int alt)
{ printf(" "); espacos(alt); printf(" "); }
void print7BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print7Bot(int alt)
{ printf(" "); espacos(alt); printf(" "); }

void print8Top(int alt)
{ traco(alt); }
void print8TopMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print8Mid(int alt)
{ traco(alt); }
void print8BotMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print8Bot(int alt)
{ traco(alt); }

void print9Top(int alt)
{ traco(alt); }
void print9TopMid(int alt)
{ printf("|"); espacos(alt); printf("|"); }
void print9Mid(int alt)
{ traco(alt); }
void print9BotMid(int alt)
{ printf(" "); espacos(alt); printf("|"); }
void print9Bot(int alt)
{ traco(alt); }

int main()
{
  int h;
  char num[999];
  while (scanf("%d", &h) && ler() && !(h == 0 && check()))
  {
    int printa, meio;
    for (printa = 0; printa < strlen(num); printa ++)
    {
      if (num[printa] == '0') { print0Top(h); }
      else if (num[printa] == '1') { print1Top(h); }
      else if (num[printa] == '2') { print2Top(h); }
      else if (num[printa] == '3') { print3Top(h); }
      else if (num[printa] == '4') { print4Top(h); }
      else if (num[printa] == '5') { print5Top(h); }
      else if (num[printa] == '6') { print6Top(h); }
      else if (num[printa] == '7') { print7Top(h); }
      else if (num[printa] == '8') { print8Top(h); }
      else if (num[printa] == '9') { print9Top(h); }
      if (printa < strlen(num) - 1)
      {
        printf(" ");
      }
    } printf("\n");
    for (meio = 0; meio < h; meio ++)
    {
      for (printa = 0; printa < strlen(num); printa ++)
      {
        if (num[printa] == '0') { print0TopMid(h); }
        else if (num[printa] == '1') { print1TopMid(h); }
        else if (num[printa] == '2') { print2TopMid(h); }
        else if (num[printa] == '3') { print3TopMid(h); }
        else if (num[printa] == '4') { print4TopMid(h); }
        else if (num[printa] == '5') { print5TopMid(h); }
        else if (num[printa] == '6') { print6TopMid(h); }
        else if (num[printa] == '7') { print7TopMid(h); }
        else if (num[printa] == '8') { print8TopMid(h); }
        else if (num[printa] == '9') { print9TopMid(h); }
        if (printa < strlen(num) - 1)
        {
          printf(" ");
        }
      } printf("\n");
    }
    for (printa = 0; printa < strlen(num); printa ++)
    {
      if (num[printa] == '0') { print0Mid(h); }
      else if (num[printa] == '1') { print1Mid(h); }
      else if (num[printa] == '2') { print2Mid(h); }
      else if (num[printa] == '3') { print3Mid(h); }
      else if (num[printa] == '4') { print4Mid(h); }
      else if (num[printa] == '5') { print5Mid(h); }
      else if (num[printa] == '6') { print6Mid(h); }
      else if (num[printa] == '7') { print7Mid(h); }
      else if (num[printa] == '8') { print8Mid(h); }
      else if (num[printa] == '9') { print9Mid(h); }
      if (printa < strlen(num) - 1)
      {
        printf(" ");
      }
    } printf("\n");
    for (meio = 0; meio < h; meio ++)
    {
      for (printa = 0; printa < strlen(num); printa ++)
      {
        if (num[printa] == '0') { print0BotMid(h); }
        else if (num[printa] == '1') { print1BotMid(h); }
        else if (num[printa] == '2') { print2BotMid(h); }
        else if (num[printa] == '3') { print3BotMid(h); }
        else if (num[printa] == '4') { print4BotMid(h); }
        else if (num[printa] == '5') { print5BotMid(h); }
        else if (num[printa] == '6') { print6BotMid(h); }
        else if (num[printa] == '7') { print7BotMid(h); }
        else if (num[printa] == '8') { print8BotMid(h); }
        else if (num[printa] == '9') { print9BotMid(h); }
        if (printa < strlen(num) - 1)
        {
          printf(" ");
        }
      } printf("\n");
    }
    for (printa = 0; printa < strlen(num); printa ++)
    {
      if (num[printa] == '0') { print0Bot(h); }
      else if (num[printa] == '1') { print1Bot(h); }
      else if (num[printa] == '2') { print2Bot(h); }
      else if (num[printa] == '3') { print3Bot(h); }
      else if (num[printa] == '4') { print4Bot(h); }
      else if (num[printa] == '5') { print5Bot(h); }
      else if (num[printa] == '6') { print6Bot(h); }
      else if (num[printa] == '7') { print7Bot(h); }
      else if (num[printa] == '8') { print8Bot(h); }
      else if (num[printa] == '9') { print9Bot(h); }
      if (printa < strlen(num) - 1)
      {
        printf(" ");
      }
    } printf("\n\n");
  }
  return(0);
}
