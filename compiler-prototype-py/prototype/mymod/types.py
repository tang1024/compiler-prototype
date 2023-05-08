# Import NumPy module for array manipulation
import numpy as np

# Define a custom vec3 class to represent 3D points or vectors
class vec3:
    def __init__(self, coords):
        self.x, self.y, self.z = coords

# Define a function to compute the length (Euclidean distance) of a 3D point
def length(point: vec3) -> float:
    return np.sqrt(point.x ** 2 + point.y ** 2 + point.z ** 2)

# Define a custom array class to represent arrays of custom data types
class array:
    def __init__(self, data, dtype):
        self.data = data
        self.dtype = dtype

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        if self.dtype == vec3:
            return self.dtype(self.data[index])
        else:
            return self.data[index]

    def __setitem__(self, index, value):
        self.data[index] = value

    def __repr__(self):
        return f"{self.data}"
