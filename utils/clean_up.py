"""
Quickly delete input files everywhere
"""
import os

ALLOWLISTED_DIRS = [
    './.git',
    './.vscode'
]
ALLOWLISTED_EXTENSIONS = [
    'cpp',
    'c++',
    'c',
    'py',
    'sql',
    'go',
    'zig',
    'rb',
    'md',
    'py2',
    'py3',
    'java',
    'json',
    'bf',
    'pptx',
    'png',
    'jpeg',
    'jpg',
    'gif'
]

def is_allowlisted_root(root: str) -> bool:
    for d in ALLOWLISTED_DIRS:
        if root.startswith(d):
            return True
    return False
def is_allowlisted_file(file_path: str) -> bool:
    for extension in ALLOWLISTED_EXTENSIONS:
        if file_path.endswith(extension):
            return True
    return False

size_and_file = []
for root, dirs, files in os.walk('./'):
    if is_allowlisted_root(root):
        continue

    for f in files:
        file_path = os.path.join(root, f)
        file_size = os.path.getsize(file_path)
        # Ignore files without extensions
        # if file_path.split('/')[-1].find('.') == -1:
        #     continue
        if is_allowlisted_file(file_path):
            continue
        if file_size < 10000:
            continue
        size_and_file.append((file_size, file_path))

size_and_file.sort()
with open('utils/to_be_deleted.txt', 'w') as to_be_deleted:
    for (size, f) in size_and_file:
        print(size, '|', f, file=to_be_deleted)

response = input('Are you ABSOLUTELY SURE? (say "YES, PLEASE"):\n')
if response != "YES, PLEASE":
    print("Yes, sir, nothing was deleted")
    exit(0)
print("NUKING UNWANTED FILES")
for (_, file_path) in size_and_file:
    os.remove(file_path)