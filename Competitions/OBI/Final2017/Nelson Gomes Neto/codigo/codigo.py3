n = int(input())
s = []
valid = 1
notValid = []
for i in range(n):
    adding = input()
    if (valid == 1):
        for j in s:
            #print(j, adding)
            for k in range(0, 10):
                m = 0
                while (k < 10 and j[k] == adding[m]):
                    m += 1
                    k += 1
                #print(k, m)
                if (k == 10 and m > 0):
                    b = m
                    for l in s:
                        m, t = b, 0
                        while (m < 10 and l[t] == adding[m]):
                            m += 1
                            t += 1
                        #print(m)
                        if (m == 10):
                            valid = 0
                            notValid = adding
                            break
                if (valid == 0):
                    break
            if (valid == 0):
                break

    s += [adding]

if (valid == 1):
    print("ok")
else:
    print(notValid)
