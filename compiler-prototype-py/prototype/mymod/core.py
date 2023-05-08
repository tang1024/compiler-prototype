# define an initialization function explicitly called by the user
def init():
    print("core initialized.")

# define a custom kernel class to represent kernel functions
# (actually can be a function)
class kernel:
    def __init__(self, func):            # using decorator for the parameter `func`
        self.func = func

    def __call__(self, *args, **kwargs): # like a functor in C++
        # possible additional code

        return self.func(*args, **kwargs)

# a function to execute the kernel function for each element
def launch(kernel, dim, inputs):
    for i in range(dim):
        kernel(*inputs, i)
