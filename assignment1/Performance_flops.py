import numpy as np
import time

def measure_flops(num_operations=10**8):
    # Create large random arrays
    A = np.random.rand(num_operations)
    B = np.random.rand(num_operations)

    # Start the timer
    start_time = time.time()

    # Perform a simple operation (addition, multiplication) in a loop
    C = B + A  # Multiply and add

    # End the timer
    end_time = time.time()

    # Calculate the elapsed time and FLOPS
    elapsed_time = end_time - start_time

    # Each iteration performs 2 floating point operations: multiply and add
    total_flops = num_operations

    # FLOPS (Floating Point Operations Per Second)
    flops = total_flops / elapsed_time

    print(f"Performed {total_flops} floating-point operations in {elapsed_time:.4f} seconds")
    print(f"Estimated FLOPS: {flops:.2e} FLOPS")

if __name__ == "__main__":
    measure_flops()
