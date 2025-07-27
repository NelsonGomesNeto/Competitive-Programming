def print_matrix(matrix):
    for i in range(n):
        # print("line:", i, matrix[i])
        print(*matrix[i], '')

def invert_main_diagonal(matrix):
    n = len(matrix)
    # i - j = 0
    for i in range(n // 2):
        aux = matrix[i][i]
        matrix[i][i] = matrix[n - 1 - i][n - 1 - i]
        matrix[n - 1 - i][n - 1 - i] = aux

def multiply_secondary_diagonal(matrix):
    n = len(matrix)
    # i + j = n - 1
    for i in range(n):
        matrix[i][n - 1 - i] *= 2

def transpose(matrix):
    new_matrix = []
    for j in range(n):
        line = []
        for i in range(n):
            line.append(matrix[i][j])
        new_matrix.append(line)
    for i in range(n):
        for j in range(n):
            matrix[i][j] = new_matrix[i][j]


n = int(input())
# print(n)
matrix = []
for i in range(n):
    line = list(map(int, input().split()))
    matrix.append(line)
# print("before:")
# print_matrix(matrix)

invert_main_diagonal(matrix)
# print("after invert_main_diagonal:")
# print_matrix(matrix)

multiply_secondary_diagonal(matrix)
# print("after multiply_secondary_diagonal:")
# print_matrix(matrix)

transpose(matrix)
# print("after transpose:")
print_matrix(matrix)