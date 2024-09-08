import os

allowed_langs = [".cpp", ".c", ".py"]
forbidden_files = ["generator", "copy", "debugger", "prepare"]
required_list = []
forbidden_list = ["dp", "memo", "map", "for"]

def matches_search(file):
    good_lang = False
    for allowed_lang in allowed_langs:
        if allowed_lang in file.path:
            good_lang = True
    if not good_lang:
        return False
    for forbidden_file in forbidden_files:
        if forbidden_file in file.path:
            return False

    try:
        f = open(file.path, "r", encoding='utf-8')
        file_content = ''.join(f.readlines())
        f.close()
    except:
        return False

    for required in required_list:
        if not required in file_content:
            return False
    for forbidden in forbidden_list:
        if forbidden in file_content:
            return False

    return True

def dfs(path = './'):
    good_files = set()
    for file in os.scandir(path):
        if file.is_dir():
            good_files |= dfs(file.path)
        elif file.is_file() and matches_search(file):
            good_files.add(file)
    return good_files

good_files = dfs()
print("Good files (%d)" % len(good_files))
print('\n'.join([str(good_file.path) for good_file in good_files]))
