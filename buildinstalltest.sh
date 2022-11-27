#!/bin/bash

python setup.py build
python setup.py install

python test/test.py