import hashlib


s = input().strip()

print("message:", s)
hash = hashlib.md5(s.encode('utf-8'))
print("hash:", hash.hexdigest())
