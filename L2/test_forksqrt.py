#!/usr/bin/env python3

import pytest
import math
from forksqrt import sqrt2


@pytest.mark.xfail
def test_sqr2_neg_val():
    sqrt2(-5)


@pytest.mark.xfail
def test_sqrt2_char():
    sqrt2("hello")

    
def test_sqrt2():
    assert sqrt2(9) == math.sqrt(9)
