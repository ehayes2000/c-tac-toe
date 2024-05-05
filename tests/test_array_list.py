import sys
import os
import pytest
so_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
sys.path.append(so_dir)
from ArrayList import ArrayList


def test_init():
    a = ArrayList()
    assert type(a) == ArrayList
    del a

def test_append_pop(): 
    a = ArrayList()
    for i in range(100):
        a.append(i)
    for i in reversed(range(100)):
        assert i == a.pop()
    
    try:
        a.pop()
        assert false
    except IndexError:
        pass
