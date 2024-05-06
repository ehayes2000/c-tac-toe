import gc
import tracemalloc
import sys
import os
import pytest
so_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
sys.path.append(so_dir)
from myVec import MyVec

def test_init():
    a = MyVec()
    assert type(a) == MyVec
    del a

def test_append_pop(): 
    a = MyVec()
    for i in range(100):
        a.append(i)
    for i in reversed(range(100)):
        assert i == a.pop()
    try:
        a.pop()
        assert false
    except IndexError:
        pass

def test_construct_iterable():
    a = MyVec([i for i in range(100)])    
    b = [i for i in range(100)]
    for i in range(100):
        assert a.pop() == b.pop()

def test_comparable():
    a = MyVec([i for i in range(100)])
    b = MyVec([i for i in range(100)])
    assert a == b

def test_iterable():
    data = [1,2,3,4,5,6]
    a = MyVec(data)
    for i, j in zip(data, a):
        assert i == j

def test_subscript():
    data = [1,2,3,4,5,6]
    a = MyVec(data)
    assert data[0] == 1
    assert data[1] == 2
    assert data[5] == 6
    a = MyVec([[i for i in range(3)] for i in range(3)])
    for i in range(3):
        assert a[i][0] == 0
        assert a[i][1] == 1
        assert a[i][2] == 2