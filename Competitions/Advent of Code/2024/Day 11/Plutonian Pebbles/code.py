BLINKS = 25

def Blink(stones):
    new_stones = []
    for s in stones:
        if s == 0:
            new_stones.append(1)
        elif len(str(s)) % 2 == 0:
            s_str = str(s)
            cnt = len(s_str)
            mid = cnt // 2
            new_stones.append(int(s_str[:mid]))
            new_stones.append(int(s_str[mid:]))
        else:
            new_stones.append(s * 2024)
    while len(stones): stones.pop()
    for s in new_stones: stones.append(s)

initial_stones = list(map(int, input().split()))

stones = initial_stones
for _ in range(BLINKS):
    Blink(stones)
    # print(stones)

print(len(stones))