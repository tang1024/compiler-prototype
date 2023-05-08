# Run me by: `python ./py_package_mymod.py`

# this example is based on an example provided by NVIDIA Warp project

# Import necessary modules
import numpy as np
import mymod

# Initialize the module
mymod.init()

# Set the number of points to be generated
num_points = 10

# Define the mymod kernel function
@mymod.kernel
def length_kernel(points, lengths, index):
    # Get the point at the given index
    point = points[index]
    print(f"Point: {point.x}, {point.y}, {point.z}")

    # Calculate the length (Euclidean distance) of the point from the origin
    len = mymod.length(point)
    print(f"Length: {len}")

    # Save the length in the corresponding position of the 'lengths' array
    lengths[index] = len

# Create a mymod array of 3D points with random coordinates
points = mymod.array(np.random.rand(num_points, 3), dtype=mymod.vec3)

# Print the generated points
for point in points:
    print(f"({point.x}, {point.y}, {point.z})")

# Create an array to store the lengths of the points
lengths = mymod.zeros(num_points, dtype=float)

# Print the initial values of the 'lengths' array (all zeros)
for length in lengths:
    print(f"{length}")

# Launch the mymod kernel to compute the lengths of the points
mymod.launch(kernel=length_kernel, dim=len(points), inputs=[points, lengths])

# Print the lengths of the points after the mymod kernel execution
print(lengths)

print("test done.")
