#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

int main()
{
  wchar_t loc[999] = L"portuguese";
  setlocale(LC_ALL,"");
  int frases, convert, ler, abre; wscanf(L"%d", &frases);
  wchar_t string[frases][9999], c;
  for (ler = 0; ler < frases; ler ++)
  {
    abre = 1;
    if (ler == 0)
    {
      getwchar();
    }
    fgetws(string[ler],9999,stdin);
    for (convert = 0; convert < (int) wcslen(string[ler]) - 1; convert ++)
    {
      if (string[ler][convert] == L'.')
      {
        abre ++;
      }
      else if (string[ler][convert] != L' ' && abre > 0)
      {
        abre --;
        if (iswlower(string[ler][convert]))
        {
          string[ler][convert] = towupper(string[ler][convert]);
        }
      }
    }
    wprintf(L"%ls", string[ler]);
  }
  return(0);
}
