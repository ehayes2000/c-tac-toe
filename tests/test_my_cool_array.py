import sys
import os
import pytest
so_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
sys.path.append(so_dir)
from myCoolCArray import MyCoolCArray 


def test_init():
    a = MyCoolCArray()
    assert type(a) == MyCoolCArray
    del a

def test_append_pop(): 
    a = MyCoolCArray()
    for i in range(100):
        a.append(i)
    for i in reversed(range(100)):
        assert i == a.pop()
    
    try:
        a.pop()
        assert false
    except IndexError:
        pass
