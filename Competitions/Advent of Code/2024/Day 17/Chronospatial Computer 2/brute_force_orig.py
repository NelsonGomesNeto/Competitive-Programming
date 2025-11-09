from heapq import heappush, heappop

def Eval(A):
    C = ((A & 0b111) ^ 0b10)
    B = C ^ (A >> C) ^ 0b11
    B = B & 0b111
    return B

instruction_target = [2,4,1,2,7,5,1,3,4,3,5,5,0,3,3,0]
# instruction_target = [2,4]

def Good(A, instructions):
    curr = A
    for i in instructions:
        res = Eval(curr)
        if res != i:
            return False
        curr >>= 3
    return True

def Search(curr = 0, i = 0):
    # for A in range(int(1e5)):
    #     if not Good(A, instruction_target): continue
    #     print(A, bin(A))
    if i == len(instruction_target):
        print(curr, bin(curr))
        return True
    for A in range(1 << 12):
        nxt = A
        if curr != 0:
            nxt = int('0b' + bin(A)[2:] + bin(curr)[2:], base=2)
        if not Good(nxt, instruction_target[:i+2]): continue
        if Search(nxt, i + 2): return True
    return False

def Search2():
    # for A in range(int(1e5)):
    #     if not Good(A, instruction_target): continue
    #     print(A, bin(A))
    visited = set()
    q = []
    def Push(nxt_curr, nxt_i):
        heappush(q, ((-nxt_i, nxt_curr), nxt_curr, nxt_i))
    Push(0, 0)
    ans = 1 << 999
    cnt = 0
    while len(q):
        _, curr, i, = heappop(q)
        if i == len(instruction_target):
            if curr < ans:
                ans = curr
                print(ans, flush=True)
            # cnt += 1
            # if cnt > 1e6: break
            continue

        if curr in visited:
            continue
        visited.add(curr)

        for A in range(1 << 9):
            nxt = A
            if curr != 0:
                nxt = int('0b' + bin(A)[2:] + bin(curr)[2:], base=2)
            if not Good(nxt, instruction_target[:i+2]): continue
            Push(nxt, i + 2)
    print(ans, bin(ans))

Search2()
