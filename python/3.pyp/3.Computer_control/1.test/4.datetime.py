#!/usr/bin/env python
# coding=utf-8

import datetime

def total_timer(times):
    td = datetime.timedelta(0)
    duration = sum([datetime.timedelta(minutes = m,seconds = s) for m, s in times],td)
    return duration 
times1 = [(2,36),
         (3,35),
         (3,45),
         ]
times2 = [(3,0),
         (5,13),
         (4,12),
         (1,10),
         ]
assert total_timer(times1) == datetime.timedelta(0,596)
assert total_timer(times2) == datetime.timedelta(0,815)

print("Tests passed,\n"
      "First test total: %s\n"
      "Second test total:%s" %(total_timer(times1),total_timer(times2)))
