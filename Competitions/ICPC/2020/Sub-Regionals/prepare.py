import os

for i in range(14):
    problem = chr(i + ord('A'))
    try:
        os.mkdir(problem)
    except Exception:
        pass

    try:
        os.mkdir(problem + "/input")
    except Exception:
        pass

    try:
        os.system("touch " + problem + "/input/" + problem + "_1")
    except Exception:
        pass

    try:
        os.mkdir(problem + "/output")
    except Exception:
        pass

    try:
        os.system("touch " + problem + "/output/" + problem + "_1")
    except Exception:
        pass

    try:
        os.system("touch " + problem + "/" + problem + ".cpp")
    except Exception:
        pass