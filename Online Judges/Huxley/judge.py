import os
from filecmp import cmp

ROOT = "190AltasAventuras"

def Verdinho(output):
    with open("out", "r") as my, open(output, "r") as cor:
        my_lines, cor_lines = my.readlines(), cor.readlines()
        if len(my_lines) != len(cor_lines): return False
        for my_line, cor_line in zip(my_lines, cor_lines):
            if my_line.strip() != cor_line.strip():
                return False
    return True

test_cases = []
for folder_rel in os.listdir(ROOT):
    folder = os.path.join(ROOT, folder_rel)
    if not os.path.isdir(folder): continue
    for file_rel in os.listdir(folder):
        file = os.path.join(folder, file_rel)
        if not os.path.isfile(file): continue
        if file_rel.startswith("out"): continue
        index = int(file_rel.replace("in", ""))
        test_cases.append((file, os.path.join(folder, "out" + str(index))))

for input, output in test_cases:
    os.system("./p < %s > out" % input)
    if not Verdinho(output):
        print("Failed test", output)
print("PASSOU!")