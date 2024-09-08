while True:
    try:
        letters = set(input()[1:-1].split(', '))
        if '' in letters:
            letters.remove('')
    except EOFError:
        break
    print(len(letters))

