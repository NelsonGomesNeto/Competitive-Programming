import os
import subprocess


# days = [1, 2, 3, 4, 5]
days = [5]
print(days)

for day in [f'Day {d}' for d in days]:
    for problem in os.listdir(day):
        path = os.path.join(day, problem)
        if not os.path.isdir(path): continue
        in_file = os.path.join(path, "in.txt")
        out_file = os.path.join(path, "out.txt")
        print(path)
        if os.path.exists(os.path.join(path, "code.cpp")):
            subprocess.call("g++ code.cpp -o p -std=c++23".split(), cwd=path)
            with open(in_file) as stdin, open(out_file, 'w') as stdout:
                subprocess.call("./p".split(), stdin=stdin, stdout=stdout, cwd=path)
        else:
            with open(in_file) as stdin, open(out_file, 'w') as stdout:
                subprocess.call("pypy3 code.py".split(), stdin=stdin, stdout=stdout, cwd=path)