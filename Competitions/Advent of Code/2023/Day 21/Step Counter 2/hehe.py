adj1 = [64, 54, 36, 28, 16]
adj2 = [69, 48, 39, 24, 17]

def deltas(arr: list):
    return list([arr[i] - arr[i + 1] for i in range(len(arr) - 1)])

print(adj1, deltas(adj1))
print(adj2, deltas(adj2))