def p():
    import ast
    x = 1
    y = 1
    while (not(x == 0 & y == 0)):
        x, y, *rest = [float() for e in ast.literal_eval().split()]
        yMax = 3 * x
        yMin = x / 3
        if (x > 0):
            if (y <= yMax & y >= yMin):
                print("INTERIOR")
            else:
                print("EXTEIOR")
        else:
            if (y >= yMax & y <= yMin):
                print("INTEIROR")
            else:
                print("EXTERIOR")
