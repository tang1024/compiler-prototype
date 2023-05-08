import sys # sys.exit()
import ctypes

# Load the C library
lib = ctypes.CDLL("../target/mymod.dll")

# Define the argument and return types for the add function
lib.add.argtypes = [ctypes.c_int, ctypes.c_int]
lib.add.restype = ctypes.c_int

lib.session_begin.restype = ctypes.c_int

##########
# session
if(lib.session_begin() == 1):
    sys.exit("Failed to init the session.")

# call the C function, add
result = lib.add(2, 3)
# print the result
print("Result:", result)

lib.session_end()
##########
