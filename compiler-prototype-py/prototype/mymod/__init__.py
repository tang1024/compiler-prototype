################################################################################
# Package-level imports
from .core import *
from .types import *
from .utility import *

################################################################################
# Package-level constants
CONSTANT_1 = "value1"
CONSTANT_2 = "value2"

################################################################################
# Package-level functions or classes
def package_level_function():
    pass

class PackageLevelClass:
    pass

################################################################################
# Initialization code
print("[mymod] Initializing the package...")

# `__all__` variable explicitly specifies the public API of the package.
# The `__all__` variable should be a list of strings containing the names of functions, classes, or variables. 
# When users import the package using a wildcard import (e.g., `from package import *`), only the names listed in `__all__` will be imported.
#__all__ = ['']

# do the init
#_init()

print("[mymod] The package is initialized.")
