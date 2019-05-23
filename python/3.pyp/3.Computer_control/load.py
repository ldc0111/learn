#!/usr/bin/env python
# coding=utf-8


import json
with open("file", "r") as fin:
    data = json.loads(fin.read())
    print(data["username"])
    print(data["password"])
