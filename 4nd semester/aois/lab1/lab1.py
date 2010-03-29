#!/usr/bin/python
# -*- coding: utf-8 -*-

from random import random

# incomplete a little bit

size = int(raw_input('Enter matrix size: '))

table = [[int(random()+0.5) for i in xrange(0, size)] for x in xrange(0, size)]

for row in table:
    print row

print

register = [0 for i in xrange(0, size)]

print "Register before loading:"

for i in register:
    print i

print

column = int(raw_input('Enter column to load into register: '))

print

i = 0
for row in table:
    register[i] = row[column]
    i += 1

print "Register after loading:"
for i in register:
    print i

print

mask = [int(random()+0.5) for i in xrange(0, size)]

print "Mask:"
for i in mask:
    print i

print

column = int(raw_input('Enter column to load into register with mask: '))

print

i = 0
while i < size:
    if mask[i]:
        register[i] = table[i][column]
    i += 1

print "Register after loading with mask:"

for i in register:
    print i

print

register2 = [int(random()+0.5) for i in xrange(0, size)]

print "Second register:"

for i in register2:
    print i

print

def f0(x1, x2):
    return 0

def f1(x1, x2):
    if x1 and x2:
        return 1
    else:
        return 0

def f2(x1, x2):
    if x1 and not x2:
        return 1
    else:
        return 0

def f3(x1, x2):
    if x1:
        return 1
    else:
        return 0

def f4(x1, x2):
    if not x1 and x2:
        return 1
    else:
        return 0

def f5(x1, x2):
    if x2 and not x1:
        return 1
    else:
        return 0

def f6(x1, x2):
    if (not x1 and x2) or (x1 and not x2):
        return 1
    else:
        return 0

def f7(x1, x2):
    if x1 or x2:
        return 1
    else:
        return 0

def f8(x1, x2):
    if not x1 and not x2:
        return 1
    else:
        return 0

def f9(x1, x2):
    if (not x1 and not x2) or (x1 and x2):
        return 1
    else:
        return 0

def f10(x1, x2):
    if not x2:
        return 1
    else:
        return 0

def f11(x1, x2):
    if not x1 and x2:
        return 0
    else:
        return 1

def f12(x1, x2):
    if not x1:
        return 1
    else:
        return 0

def f13(x1, x2):
    if x1 and not x2:
        return 0
    else:
        return 1

def f14(x1, x2):
    if x1 and x2:
        return 0
    else:
        return 1

def f15(x1, x2):
    return 1

print "Applying f6:"

i = 0
while i < size:
    print f6(register[i], register2[i])
    i += 1

print

print "Applying f9:"

i = 0
while i < size:
    print f9(register[i], register2[i])
    i += 1