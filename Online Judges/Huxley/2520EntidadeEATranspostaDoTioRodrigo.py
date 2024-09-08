def invert_main_diagonal(n, matrix):
    for i in range(n // 2):
        aux = matrix[i][i]
        matrix[i][i] = matrix[n - i - 1][n - i - 1]
        matrix[n - i - 1][n - i - 1] = aux

def multiple_secondary_diagonal(n, matrix):
    for i in range(n):
        matrix[i][n - i - 1] *= 2

def transpose(n, matrix):
    transposed_matrix = []
    for j in range(n):
        line = []
        for i in range(n):
            line.append(matrix[i][j])
        transposed_matrix.append(line)
    return transposed_matrix

def print_matrix(n, matrix):
    for i in range(n):
        for j in range(n):
            print(matrix[i][j], end=' ')
        print()

n = int(input())

matrix = []
for i in range(n):
    line = input()
    matrix.append(list(map(int, line.split())))

invert_main_diagonal(n, matrix)

multiple_secondary_diagonal(n, matrix)

matrix = transpose(n, matrix)

print_matrix(n, matrix)