import os
import re
import sys

from stat import S_IREAD, S_IWRITE

mkd = set()

def dfs(include_dir: str, path: str) -> tuple[set[str], list[str]]:
    a = set()
    b = []
    with open(path, 'r') as file:
        for line in file:
            match = re.search(r'#include\s+(\S+)', line)
            if match:
                a.add(match.group(1))
            else:
                b.append(line)

    c = set()
    d = []
    for x in a:
        if x.startswith('<'):
            c.add(x)
        elif x not in mkd:
            e = dfs(include_dir, include_dir + x[1:-1])
            c.update(e[0])
            d += e[1]

    return c, d + b


if __name__ == '__main__':
    includes, body = dfs(f'{sys.argv[1]}/include/', f'{sys.argv[1]}/src/{sys.argv[2]}.cpp')
    filename = f'{sys.argv[1]}/out/{sys.argv[2]}.cpp'
    if os.path.isfile(filename):
        os.chmod(filename, S_IWRITE)
    with open(filename, 'w') as file:
        for x in sorted(includes):
            file.write(f'#include {x}\n')
        for line in body:
            file.write(line)
    os.chmod(filename, S_IREAD)
