import sys
sys.setrecursionlimit(2**20)

def solve(correct, student, j, i, end):
    if (i == end or j == end):
        return(0)
    best = solve(correct, student, j + 1, i, end)
    aux, aux2 = solve(correct, student, j, i + 1, end), 0
    if (correct[j] == student[i]):
        aux2 = solve(correct, student, j + 1, i + 1, end) + 1
    best = max(best, aux, aux2)
    return(best)

events = int(input())
correct = list(map(int, input().split()))
while (True):
    try:
        student = list(map(int, input().split()))
        answer = solve(correct, student, 0, 0, events)
        print(answer)
    except EOFError as e:
        break
