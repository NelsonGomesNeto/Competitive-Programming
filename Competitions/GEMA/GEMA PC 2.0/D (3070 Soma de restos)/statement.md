# Descrição
Dado um array **A** e um número **m**.

Responda **q** queries do tipo: **l** **r** **k** (Quantos números em **A** da posição **l** até **r** tem resto de divisão por **m** igual a **k**).

# Entrada
A primeira linha da entrada terá dois inteiros **n** e **m** (1 <= **n**, **m** <= 10^3), . A segunda linha terá os **n** de **A**. A terceira linha terá um inteiro **q** (1 <= **q** <= 10^5), indicando a quantidade de queries. E então virão **q** linhas, uma para cada query; contendo **l**, **r** e **k** (1 <= **l** <= **r** <= **n**, 0 <= **k** < **m**).

# Saída
Para cada query, imprima um inteiro com a resposta dela.