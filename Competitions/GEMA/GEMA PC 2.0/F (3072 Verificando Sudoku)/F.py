def valid(n):
    for i in range(n):
        line = [False] * n
        column = [False] * n
        for j in range(n):
            line[sudoku[i][j] - 1] = True
            column[sudoku[j][i] - 1] = True
        if min(line) == False or min(column) == False:
            return False
    sqrtn = int(n**0.5)
    for i in range(0, n, sqrtn):
        for j in range(0, n, sqrtn):
            block = [False] * n
            for ii in range(sqrtn):
                for jj in range(sqrtn):
                    block[sudoku[i + ii][j + jj] - 1] = True
            if min(block) == False:
                return False
    return True

n = int(input())
sudoku = [list(map(int, input().split())) for i in range(n)]
print("YES" if valid(n) else "NO")