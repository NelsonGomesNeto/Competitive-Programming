def fatorial(n):
    if (n <= 1):
        return(1)
    return(n * fatorial(n - 1))

while (True):
    string = input()
    if (string == '0'):
        break
    alphabet = [0] * 35
    total = 0
    for i in string:
        if (alphabet[ord(i) - ord('a')] == 0):
            total += 1
        alphabet[ord(i) - ord('a')] += 1
    print(fatorial(total))
