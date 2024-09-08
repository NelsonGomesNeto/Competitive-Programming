t = int(input())

def cnt(s: str):
    total = 0
    for i in range(len(s) + 4):
        total += s[i : i + 4] == "haha"
    return total

def reduce(s: str):
    if len(s) >= 10:
        print(s, s[:4], s[-4:], s[4:-4])
        return s[:4] + s[-4:], cnt(s[4:-4])
    else:
        return s, cnt(s)

for _ in range(t):
    n = int(input())
    variables = {}
    ans = 0
    for i in range(n):
        line = input()
        if ":=" in line:
            var, s = line.split(" := ")
            variables[var] = [s, cnt(s)]
            ans = variables[var][1]
            # print(variables[var][0])
        else:
            var, ab = line.split(" = ")
            a, b = ab.split(" + ")
            s = variables[a][0] + variables[b][0]
            s, total = reduce(s)
            total += variables[a][1] + variables[b][1]
            variables[var] = [s, total]
            ans = variables[var][1]
            # print(variables[var][0])
    print(ans)
