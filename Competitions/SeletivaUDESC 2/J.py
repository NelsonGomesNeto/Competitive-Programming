DEBUG = 0

t = int(input())
for i in range(t):
    line = input()
    line = line.replace('=', "==")
    can = -1
    for j in range(10):
        char = chr(j + ord('0'))
        if (char in line): continue
        copy = line.replace('?', char)
        # if ("-0" in copy): continue
        symbol = '+' if '+' in copy else '*' if '*' in copy else '-'
        each = copy.split("==")
        each += each.pop(0).split(symbol)
        for kk in range(len(each)):
            each[kk] = each[kk].strip('-')
        has = 0
        for e in each:
            if (e == ''): continue
            if (e[0] == '0' and len(e) > 1):
                has = 1
        if (has): continue
        try:
            if (eval(copy)):
                can = j
                break
        except:
            pass
    print(can)