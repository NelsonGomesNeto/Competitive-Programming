operators = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3, '(': 0, ')': 0}

def solve(expression):
    stack = []
    ans = ""
    for e in expression:
        # print(stack)
        if (e not in operators):
            ans += e
        elif (e == '('):
            stack += [e]
        elif (e == ')'):
            while (stack and stack[len(stack) - 1] != '('):
                ans += stack.pop(len(stack) - 1)
            stack.pop(len(stack) - 1)
        else:
            while (stack and operators[e] <= operators[stack[len(stack) - 1]]):
                ans += stack.pop(len(stack) - 1)
            stack += [e]
    while (stack):
        ans += stack.pop(len(stack) - 1)
    return(ans)


t = int(input())
while (t):
    expression = input()
    # print(expression)
    ans = solve(expression)
    print(ans)
    t -= 1