from pathlib import Path
import os
import sys

def find_old_include_guard_text(datas):
    include_guard_text = ''
    for data in datas:
        if '#ifndef' in data:
            include_guard_text = data.replace('#ifndef', '').strip()
            print (include_guard_text)
        
        if '#define' in data:
            if include_guard_text in data:
                return include_guard_text
        
    return ''

def new_include_guard_text(path):
    base_name = os.path.basename(path)
    include_guard_text = base_name.replace('.', '_')
    include_guard_text = include_guard_text.upper()

    return include_guard_text

def replaced_code(datas, old_include_guard_text, new_include_guard_text):
    if 0 == len(old_include_guard_text):
        return datas
    if 0 == len(new_include_guard_text):
        return datas

    return datas.replace(old_include_guard_text, new_include_guard_text)
    
def main():
    args = sys.argv

    p = ""
    is_create_bak = True
    target_extension = "**/*.h"

    if 3 < len(args):
        print('Too many arguments!')
        exit()

    if '-b' == args[1]:
        is_create_bak = False
        p = Path(args[2])
    else :
        p = Path(args[1])

    for path in list(p.glob(target_extension)):
        all_data = path.read_text()
        datas = all_data.splitlines()
        
        old_include_guard_text = find_old_include_guard_text(datas)
        code = replaced_code(all_data, old_include_guard_text, new_include_guard_text(path))

        if True == is_create_bak:
            os.rename(str(path), str(path) + '.bak')

        f = open(str(path), 'w')
        f.write(code)
        f.close()

main()
print("\nInclude guard formatted!")
