#!/usr/bin/env python3

import pytest
import math
from forksqrt import sqrt2


@pytest.mark.xfail
def test_sqr2_neg_val():
    sqrt2(Decimal(-5))


@pytest.mark.xfail
def test_sqrt2_char():
    sqrt2("hello")


def test_sqrt2():
    for i in range(1, 100):
        assert round(float(sqrt2(i)), 15) == round(math.sqrt(i), 15)
