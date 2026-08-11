import hashlib

# TARGET = '00000'
TARGET = '000000'


def FindSmallest(s: str):
  for i in range(1, int(1e7) + 1):
    h = hashlib.md5((s + str(i)).encode('utf-8'))
    if h.hexdigest().startswith(TARGET):
      return i
  return -1


s = input().strip()

suffix = FindSmallest(s)
h = hashlib.md5((s + str(suffix)).encode('utf-8'))
print(s, suffix, h.hexdigest())
print(f"ans: {suffix}")
