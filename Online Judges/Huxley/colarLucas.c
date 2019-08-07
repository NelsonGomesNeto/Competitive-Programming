#include <stdio.h>

int main() {
    int n, i, max = 0;
    scanf("%d", &n);
    char colar[n];
    for (i = 0; i < n; i++)
        scanf(" %c", &colar[i]);
    for (i = 0; i < n; i++) {
        int pedrasdir = 0, pedrasesq = 0;
        int cont = i, var = i + 1;
        char coratual = colar[i];

        while (colar[cont] == coratual || colar[cont] == 'w' || coratual == 'w') {
            pedrasesq++;
            cont--;
            if (coratual == 'w' && colar[cont] != 'w')
                coratual = colar[cont];
            if (cont == -1)
                cont = n-1;
            if (pedrasesq == n)
                break;
        }
        if (var == n)
            var = 0;
        coratual = colar[var];
        while (colar[var] == coratual  || colar[var] == 'w' || coratual == 'w') {
            pedrasdir++;
            var++;
            if (coratual == 'w' && colar[var] != 'w')
                coratual = colar[var];
            if (var == n)
                var = 0;
            if (pedrasdir == n)
                break;
        }
        if (pedrasdir + pedrasesq > max)
            max = pedrasdir + pedrasesq;
    }
    if (max > n)
        max = n;
    printf("%d\n", max);
    return 0;
}
