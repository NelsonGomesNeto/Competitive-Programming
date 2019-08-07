def tryAll(i, n):
    if (i == n // 2):
        print(*b)
        return(0)
    ans = 0
    for j in range(26):
        if (letters[j]):
            letters[j] -= 1
            b[i] = chr(j + ord('a'))
            ans += 1 + tryAll(i + 1, n)
            letters[j] += 1
    return(ans)

n = int(input())
b = [0] * n
line = str(input())
letters = [0] * 26
for i in line:
    letters[ord(i) - ord('a')] += 1

ans = tryAll(0, n)
print(ans)