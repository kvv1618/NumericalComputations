import subprocess
import matplotlib.pyplot as plt

relative_error = []

for precision in range(5, 101):
    output = subprocess.run(['./additionErrors.sh' , f'{precision}'], capture_output=True, text=True)
    relative_error.append(float(
        (output.stdout.split('\n')[4]).split(' ')[-1]
    ))

plt.plot(range(5, 101), relative_error, 'ro-')
plt.xlabel('Precision')
plt.ylabel('Relative Error')
plt.title('Relative Error vs Precision')
plt.show()
