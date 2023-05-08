import numpy as np
from .types import array

# Define a function to create an array filled with zeros
def zeros(dim, dtype=float):
    return array(np.zeros(dim, dtype=dtype), dtype)
