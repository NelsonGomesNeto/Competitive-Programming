password, guess = 43214434, 525423156231
ans = password ^ guess

k = 2

new_password, p = 0, 1
while password > 0 or guess > 0:
    a, b = password % k, guess % k
    new_password += p * ((a + b) % k)
    p *= k
    password //= k
    guess //= k

print(new_password, ans)