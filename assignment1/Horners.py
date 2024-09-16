import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-N', '--degrees', type=str, help='Degrees of the polynomial')
parser.add_argument('-P', '--poly', type=str, help='List of coefficients of the polynomial')
parser.add_argument('-Xs', '--xstart', type=float, help='Value of x start')
parser.add_argument('-Xe', '--xend', type=float, help='Value of x end')

args = parser.parse_args()

poly_dict = {}
if args.poly and args.degrees:
    for key,val in zip(args.degrees.split(' '), args.poly.split(' ')):
        poly_dict[int(key)] = int(val) 
else:
    poly_dict = {5: 4, 4: 7, 3: 8, 2: -20, 1: -5, 0: 10}

def horner(poly_dict, x, poly_degrees):

    # Initialize result
    result = poly_dict[poly_degrees[0]]  
    cur_exp = poly_degrees[0]
  
    # Evaluate value of polynomial
    # using Horner's method
    for i in poly_degrees[1:]:
        gap = cur_exp - i
        result = result * (x**gap) + poly_dict[i]
        cur_exp = i
  
    return result

def poly_eval(poly_dict, x, poly_degrees):
    # Declaring the result
    result = 0
    
    # Running a for loop to traverse through the list
    for i in poly_degrees:
    
        # Declaring the variable Sum
        Sum = poly_dict[i]
    
        # Running a for loop to multiply x (n-i-1)
        # times to the current coefficient
        for j in range(0,i):
            Sum = Sum * x
    
        # Adding the sum to the result
        result = result + Sum

    return result

n = len(poly_dict)
poly_degrees =  sorted(poly_dict.keys(), reverse=True)
x_range, normal_arr, horner_arr = [], [], []
x = -2 if args.xstart is None else args.xstart
x_end = 3 if args.xend is None else args.xend
while x<=x_end:
    x_range.append(x)
    horner_arr.append(horner(poly_dict, x, poly_degrees))
    normal_arr.append(poly_eval(poly_dict, x, poly_degrees))
    x+=(0.5 if args.xend is None else 19.5)

abs_error = [abs(horner_arr[i]-normal_arr[i]) for i in range(len(horner_arr))]
relative_error = [abs_error[i]/normal_arr[i] for i in range(len(horner_arr))]

fig, axs = plt.subplots(3,1 , figsize=(10, 10))
axs[0].plot(x_range, horner_arr, 'ro-', label='Horner\'s Method')
axs[0].plot(x_range, normal_arr, 'bo-', label='Normal Method')
axs[0].set_xlabel('x')
axs[0].set_ylabel('p(x)')
axs[0].set_title('Horner\'s Method vs Normal Method')
axs[0].legend()

axs[1].plot(x_range, relative_error, 'ro-', label='Relative Error')
axs[1].set_xlabel('x')
axs[1].set_ylabel('Relative Error')
axs[1].set_title('Relative Error')

axs[2].plot(x_range, abs_error, 'ro-', label='Absolute Error')
axs[2].set_xlabel('x')
axs[2].set_ylabel('Absolute Error')
axs[2].set_title('Absolute Error')

plt.show()
