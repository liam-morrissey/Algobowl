#!/usr/bin/python3

import sys

for fname in sys.argv:
    if(fname.find("verify.py") != -1):
        continue;
    print(fname)
    dic = {}
    with open(fname, 'r') as f:
        f.readline()
        lines = f.readlines();
        for line in lines:
            values = line.split(' ')
            for value in values:
                value = value.strip()
                if value in dic:
                    dic[value] = dic[value] + 1
                    print("Error Doubled down")
                else:
                    dic[value] = 1
    print(f"Dic Size: {len(dic)}")
