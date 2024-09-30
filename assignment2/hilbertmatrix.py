import numpy as np
import argparse

parser = argparse.ArgumentParser(description='Hilbert matrix')
parser.add_argument('--size', type=int, default=9, help='Size of the Hilbert matrix')
parser.add_argument('sols', metavar='B', type=float, nargs='+', help='Solutions of the system of equations')
args = parser.parse_args()

size = 5 if not args.size else args.size

H_custom = np.array([[1 / (i + j + 1) for j in range(size)] for i in range(size)])

print("Hilbert matrix of size", size)
for row in H_custom:
    for elem in row:
        print("{:.4f}".format(elem), end=" ")
    print()

B = np.array(args.sols)

X_solution_custom = np.linalg.solve(H_custom, B)

cond_number_custom = np.linalg.cond(H_custom)
print("Condition number of the Hilbert matrix of size", size, "is", cond_number_custom)

print("Solution of the system of equations:")
for i in X_solution_custom:
    print("{:.4f}".format(i))
