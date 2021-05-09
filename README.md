# Simple polynomial equation solver.

MacOS - [![Build Status](https://travis-ci.com/dolovnyak/simple-equation-solver.svg?branch=master)](https://travis-ci.com/dolovnyak/simple-equation-solver)
###
Test coverage: 57% lines covered, 44% branches covered

This program simplifies and solves a polynomial second or lower degree equation.
-------
For example:
```
./simple-equation-solver "2x^2 + x = 5"
Reduced form: 2 * X^2 + 1 * X^1 - 5 * X^0 = 0
Polynomial degree: 2
Discriminant = 41, it's strictly positive, there are two solutions:
-1.85078
1.35078
```
It also supports complex numbers in output:
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
cmake .
make

./simple-equation-solver "first argument input" 
or
./simple-equation-solver
write into standard input stream
```
