from random import randint
import functools

class Node:
    def __init__(self, op, children):
        self.op = op
        self.children = children
    def __repr__(self) -> str:
        return str(self)
    def apply_op(self) -> int:
        op = {1: '+', 2: '*', 3: '-'}[self.op]
        if op == '+':
            return functools.reduce(lambda a, b: Leaf(a.apply_op() + b.apply_op()), self.children, Leaf(0)).val
        if op == '*':
            return functools.reduce(lambda a, b: Leaf(a.apply_op() * b.apply_op()), self.children, Leaf(1)).val
        if op == '-':
            return functools.reduce(lambda a, b: Leaf(a.apply_op() - b.apply_op()), self.children, Leaf(0)).val
    def __str__(self) -> str:
        op = {1: '+', 2: '*', 3: '-'}[self.op]
        return op + ' ' + str(self.children)

class Leaf(Node):
    def __init__(self, val) -> None:
        self.val = val
    def __repr__(self) -> str:
        return str(self)
    def __str__(self) -> str:
        return 'l[' + str(self.val) + ']'
    def apply_op(self) -> int:
        return self.val
    
leaf_set = []
leaf_set.append(Leaf(1))
leaf_set.append(Leaf(2))
# leaf_set.append(Leaf(20))
# leaf_set.append(Leaf(69))
# leaf_set.append(Leaf(420))
# leaf_set.append(Leaf(100))

print(leaf_set)


choices = []
order   = []

N = 7

for i in range(N):
    order.append(randint(0, leaf_set.__len__() - 1))


while N > 1:
    picked = randint(2, N)
    op = randint(1, 3)
    choices.append((picked, op))
    N = N - picked + 1
    
print(choices, len(order))
    

stack = []

for o in order:
    stack.append(leaf_set[o])

print(stack)


while stack.__len__() > 1:
    ch, op = choices.pop(0)
    n = Node(op, stack[:ch])
    stack = stack[ch:] + [n]
    
print(stack)
print(stack[0].apply_op())
