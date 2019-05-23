#!/usr/bin/env python
# coding=utf-8

dict ={'lily':100,'bob':88,'alice':59}
#print dict['bob'] + 1
dict['leijun'] = 99
del dict['alice']
sys.exit(0)
#print dict.items()
#print dict.keys()
#print '%(lily)d,' % dict
#print 'The grades are lily: %(lily)d, bob: %(bob)d, alice: %(alice)d' % dict
print dict.items()
print dict.keys()
print dict['bob'] + 1
