#!/usr/bin/python 
# -*- coding: utf-8 -*-

from copy import copy

expression = raw_input('Enter expression and press Enter: ')

left_part  = expression[:expression.find('=')]
right_part = expression[expression.find('=')+1:]

# left part - right part must be zero
new_expression = '('+left_part+')-('+right_part+')'

# building stack and polish line

function_symbols = ['u', 'n', '\\', '-']

stack = []
result = ''
sets = []

while len(new_expression) > 0:
    symbol = new_expression[0]
    if symbol >= 'A' and symbol <= 'Z':
        result += symbol
        if sets.count(symbol) == 0:
            sets.append(symbol)
    elif symbol == '(':
        stack.append(symbol)
    elif symbol == ')':
        last_stack_symbol = stack.pop()
        while last_stack_symbol != '(':
            result += last_stack_symbol
            last_stack_symbol = stack.pop()
    elif function_symbols.count(symbol):
        while len(stack) > 0 and stack[-1] != '(':
            result += stack.pop()
        stack.append(symbol)
    else:
        raise ValueError('Invalid symbol in expression: '+symbol)
    new_expression = new_expression[1:]

while len(stack) > 0:
    result += stack.pop()


def get_variant(sets):
    """Generator maker"""
    variant = dict((i, False) for i in sets)
    while True:
        all_true = True
        for i in variant.values():
            if i != True:
                all_true = False
                break
        yield variant
        i = 0
        for i in variant.keys():
            if not variant[i]:
                variant[i] = True
                break
            else:
                variant[i] = False
        if all_true:
            raise StopIteration

is_correct = True

for v in get_variant(sets):
    result_copy = result
    local_stack = []
    variant = copy(v)
    while len(result_copy) > 0:
        symbol = result_copy[0]
        if symbol >= 'A' and symbol <= 'Z':
            local_stack.append(symbol)
        elif function_symbols.count(symbol):
            rigth_operand  = local_stack.pop()
            left_operand   = local_stack.pop()
            representation = left_operand+symbol+rigth_operand
            if symbol == 'u':
                variant[representation] = variant[left_operand] or \
                                          variant[rigth_operand]
                local_stack.append(representation)
            elif symbol == 'n':
                variant[representation] = variant[left_operand] and \
                                          variant[rigth_operand]
                local_stack.append(representation)
            elif symbol == '\\':
                variant[representation] = variant[left_operand] and \
                                          not variant[rigth_operand]
                local_stack.append(representation)
            elif symbol == '-':
                variant[representation] = (variant[left_operand] and
                                           not variant[rigth_operand]) or \
                                          (not variant[left_operand] and \
                                           variant[rigth_operand])
                local_stack.append(representation)
            else:
                raise ValueError('Shit happend in another place!!1')
        else:
            raise ValueError('Shit happend!!1')
        result_copy = result_copy[1:]
    if variant[local_stack.pop()]:
        is_correct = False
        break

# trenary hack. ololo %)
print is_correct and 'Sameness' or 'Equation'