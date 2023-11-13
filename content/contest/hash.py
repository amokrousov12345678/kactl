'''
* Author: Anton Mokrousov
* Description: Hashes a file, ignoring all
* whitespace and comments.
'''

import hashlib, pathlib, re, sys
if len(sys.argv) >= 2:
    data_b = pathlib.Path(sys.argv[1]).read_bytes()
else:
    data_b = sys.stdin.read().encode('utf-8')
data = data_b.decode('ascii')
data = re.sub('//.*?\n|/\*.*?\*/', '', data, flags=re.S)
data = ''.join(data.split()).encode('utf-8')
print(hashlib.md5(data).hexdigest()[0:6])
if len(sys.argv) >= 2: input()
