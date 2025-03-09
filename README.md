# Runge-Kutta 4 Solver

## 📌 Project Overview
This project implements the **Runge-Kutta 4 (RK4) method** in C to numerically solve **first-order ordinary differential equations (ODEs)** of the form:

y' = f(x, y)

The program provides an interactive terminal-based interface where users can enter a differential equation, define initial conditions, choose a step size, and compute solutions iteratively. It also supports error analysis by comparing computed results with expected values.

## ✨ Features
✅ **Runge-Kutta 4 Method**: Implements RK4 integration for solving ODEs.  
✅ **Custom Equation Input**: Supports polynomial, sine, and cosine functions.  
✅ **User-Defined Step Size**: Experiment with different step sizes and analyze accuracy.  
✅ **Error Analysis**: Displays computed results alongside expected values.  
✅ **Memory-Efficient**: Uses **dynamic memory allocation** for equation storage.  
✅ **Real-Time Terminal UI**: Displays step-by-step RK4 computations.  
✅ **Data Storage & Retrieval**: Supports storing results for further analysis.

## 📂 File Structure
```
.
├── project.c         # Main C program implementing RK4 method
├── report.pdf        # Detailed project report including theory and analysis
├── README.md         # Documentation file
```

## 🚀 Installation & Compilation
### Prerequisites
Ensure you have a **C compiler (GCC/Clang/MSVC)** installed on your system.

### Compilation
To compile the program, run the following command in the terminal:
```bash
gcc project.c -o runge_kutta_solver -lm
```
The `-lm` flag is required to link the **math library**.

### Running the Program
Once compiled, execute the binary with:
```bash
./runge_kutta_solver
```
The program will prompt for user input to define the ODE and initial conditions.

## 📖 Usage Guide
1. **Define the differential equation** in the form `A*y' + B*y + g(x) = 0`.
2. **Enter initial conditions** (x0, y0) and an expected result for comparison.
3. **Choose a step size** for RK4 calculations.
4. **View iterative results**, including intermediate RK4 computations (`k1, k2, k3, k4`).
5. **Compare results** against expected values and analyze error margins.
6. **Optionally, test different step sizes** for accuracy comparisons.

## 🛠 Technologies Used
- **C Programming** – Core numerical methods implementation.
- **Runge-Kutta 4 (RK4) Method** – Precision numerical integration.
- **File I/O (Binary & Text)** – Saves and retrieves computation results.
- **Dynamic Memory Allocation** – Efficient memory management for user inputs.
- **Mathematical Modeling** – Implements numerical approximation techniques.

## 📊 Example Run
```
Enter the number of elements of the function f(x): 1

The following types can be found in the function:
  - ID:1 polynomial
  - ID:2 sin(Ax)
  - ID:3 cos(Ax)

Enter the function_id for element #1
  - ID:1 polynomial
  - ID:2 sin(Ax)
  - ID:3 cos(Ax)
1

Enter the coefficient [a] of a*(x^n) :  -1
Enter exponent [n] of a*(x^n) : 1
----------------
Enter the coefficient of [A] A* y' : 2
Enter the coefficient of [B] B* y :  1
----------------
2.000000*y' + 1.000000*y + [ -1 * x^1 + ] = 0

Enter the x0 value :  0
Enter the y(0.000000) value : 1
Enter the expected result :  0.91451225
Enter the step size (h): 0.1
Enter the target value (x) :  0.2
-------------
k1 = -0.500000  k2 = -0.462500  k3 = -0.463438  k4 = -0.426828
iter #1 y(0.100000) = 0.953688

k1 = -0.426844  k2 = -0.391173  k3 = -0.392065  k4 = -0.357241
iter #2 y(0.200000) = 0.914512

----------------------
Runge Kutta-4 result: 0.914512
Expexted result     : 0.914512
Error value         : 0.000000

Do you want to calculate RK-4 with different stepsize (Yes:1 / No:0): 1

Enter the step size (h): 0.05
Enter the target value (x) : 0.2

-------------
k1 = -0.500000  k2 = -0.481250  k3 = -0.481484  k4 = -0.462963
iter #1 y(0.050000) = 0.975930

k1 = -0.462965  k2 = -0.444678  k3 = -0.444906  k4 = -0.426842
iter #2 y(0.100000) = 0.953688

k1 = -0.426844  k2 = -0.409009  k3 = -0.409232  k4 = -0.391613
iter #3 y(0.150000) = 0.933230

k1 = -0.391615  k2 = -0.374220  k3 = -0.374437  k4 = -0.357254
iter #4 y(0.200000) = 0.914512

----------------------
Runge Kutta-4 result: 0.914512
Expexted result     : 0.914512
Error value         : 0.000000

Do you want to calculate RK-4 with different stepsize (Yes:1 / No:0): 0

All test values:
Step Size (h) | RK-4 Result | Error Value
------------------------------------------
0.10000000    | 0.91451227  | 0.0000000188
0.05000000    | 0.91451226  | 0.0000000050
```

## 📌 Future Improvements
- Extend support for **higher-order ODEs**.
- Implement **adaptive step-size selection** for improved accuracy.
- Add **graphical visualization** of numerical solutions.

## 📝 License
This project is open-source and available under the **MIT License**.

---

## 📞 Contact

For any questions or feedback, feel free to reach out! 🚀
