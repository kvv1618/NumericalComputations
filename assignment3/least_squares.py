import numpy as np
import matplotlib.pyplot as plt

time_x, thrust_y = [], []
with open('rocket.txt', 'r') as f:
    data = f.readlines()
    for line in data[1:]:
        cols = line.split(',')
        time_x.append(float(cols[0]))
        thrust_y.append(float(cols[-1]))
        if float(cols[0]) == 1.9:
            break

time_x = np.array(time_x)
thrust_y = np.array(thrust_y)

print("Data points:")
for i in range(len(time_x)):
    print(f"({time_x[i]},{thrust_y[i]})", end = " ")
print()

coeff = []
for degree in range(3, 18):
    A = np.vstack([time_x**i for i in range(degree)]).T
    coeff.append(np.linalg.lstsq(A, thrust_y, rcond=None)[0])

for c in coeff:
    print("Coefficients for degree", len(c), ":")
    for i in range(len(c)):
        print(f"a{i} = {c[i]}", end = " ")
    print()

max_errors, avg_errors, rms_errors = [], [], []
for c in coeff:
    y = np.polyval(c[::-1], time_x)
    error = y - thrust_y
    max_errors.append(np.max(np.abs(error)))
    avg_errors.append(np.mean(np.abs(error)))
    rms_errors.append(np.sqrt(np.mean(error**2)))

plt.figure()
plt.subplot(212)
plt.plot(max_errors, 'o-', label='max error')
plt.plot(avg_errors, 'o-', label='avg error')
plt.plot(rms_errors, 'o-', label='rms error')
plt.legend(loc='upper left')
plt.subplot(211)
plt.plot(time_x, thrust_y, 'o', label='data')
for c in coeff:
    plt.plot(time_x, np.polyval(c[::-1], time_x), label=f'degree {len(c)}')
plt.legend()
plt.show()
