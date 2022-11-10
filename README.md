# Simple polynomial equation solver.

## MacOS - ![Build](https://github.com/dolovnyak/simple-equation-solver/actions/workflows/build.yml/badge.svg?branch=master)

This program simplifies and solves a polynomial second or lower degree equation.
-------
Second degree example:
```
./simple-equation-solver "2x^2 + x = 5"
Reduced form: 2 * X^2 + 1 * X^1 - 5 * X^0 = 0
Polynomial degree: 2
Discriminant = 41, it's strictly positive, there are two solutions:
-1.85078
1.35078
```
First degree example:
```
./simple-equation-solver "28x + 32x -352* 23 = 14 * x^1 * X^2/x/X"
Reduced form: 46 * X^1 - 8096 * X^0 = 0
Polynomial degree: 1
The solution is:
176
```
Discriminant = 0 example:
```
./simple-equation-solver "5 + 10X =  -5x^2"
Reduced form: 5 * X^0 + 10 * X^1 + 5 * X^2 = 0
Polynomial degree: 2
Discriminant = 0, there is one solution:
-1
```
It also have solution with complex numbers when discriminant < 0:
```
/simple-equation-solver "5 + 3x + 3x^2 = 1"
Reduced form: 4 * X^0 + 3 * X^1 + 3 * X^2 = 0
Polynomial degree: 2
Discriminant = -39, it's strictly negative, there are two complex solutions:
-0.5 - i * 1.04083
-0.5 + i * 1.04083
```

Build and run on `MacOS`:
-------

```
git submodule update --init --recursive
cmake -S . -B build
make -C build

./simple-equation-solver "first argument input" 
or
./simple-equation-solver
write into standard input stream
```
