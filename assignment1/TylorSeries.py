import numpy as np
import math
import matplotlib.pyplot as plt
import argparse
from scipy.interpolate import approximate_taylor_polynomial

parser = argparse.ArgumentParser()
parser.add_argument('-N', '--terns', type=str, help='No of terms in Taylor Series')
parser.add_argument('-A', '--evalpoint', type=str, help='Angle in radians')

args = parser.parse_args()

nu_terms = 7 if args.terns is None else int(args.terns)
eval_point = 0 if args.evalpoint is None else float(args.evalpoint)

inbuilt_sin_taylor = approximate_taylor_polynomial(np.sin, eval_point, nu_terms, 1)

x = np.linspace(-2*np.pi, 2*np.pi, 100)
y = np.sin(x)
y_taylor = inbuilt_sin_taylor(x)

sin_taylor = 0
sign_counter = -1
for n in range(0,nu_terms):
    if n%2 == 0:
        sign_counter *= -1
    if n%2 == 0:
        sin_taylor += (sign_counter * ((np.sin(eval_point) * (x-eval_point)**(n)) / math.factorial(n)))
    else:
        sin_taylor += (sign_counter * ((np.cos(eval_point) * (x-eval_point)**(n)) / math.factorial(n)))

truncation_error = y - sin_taylor

fig, ax = plt.subplots(2, 1, figsize=(10,10))
ax[0].plot(x, y, label='sin(x)')
ax[0].plot(x, y_taylor, label='Inbuilt Taylor Series')
ax[0].plot(x, sin_taylor, label='Calculated Taylor Series')
ax[0].legend()
ax[0].set_title('Taylor Series of sin(x)')
ax[0].set_xlabel('x')
ax[0].set_ylabel('y')
ax[0].set_ylim(-2, 2)

ax[1].plot(x, truncation_error, label='Truncation Error')
ax[1].legend()
ax[1].set_title('Truncation Error')
ax[1].set_xlabel('x')
ax[1].set_ylabel('y')

plt.show()
