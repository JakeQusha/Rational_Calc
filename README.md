# Rational Calculator

Simple console rational calculator written in c++. Made for fun in my free time.

## Usage
- Simply type in your equation and hit return.
- If you make syntax mistake it will show you where you made it.
- So far supported operations are:```addition (+)```, ```subtraction (-)```, ```multiplication (*)``` and ```division (/)```.
- Equation with parentheses are supported ```()```.
- Spaces do not matter.
- type ```exit``` to exit an application.

## Examples
### Valid inputs:
- ```3+3 * 3``` --> ```12``` 
- ```2-(-2)``` --> ```4``` 
- ```3/2 +-   2``` --> ```-1/2``` 
- ```2(-1/8)(2 + 2 * 2)``` --> ```-3/2```
- ```2(-1/8)(2 + 2 * 2)(19)(1/8)(3 + 3 * (-2))``` --> ```171/16```
### Invalid inputs:
- ```2(-1/8)(2 + 2 * 2)(19)(1/8))(3 + 3 * (-2))``` 
 ```
Unexpected Closing Parenthesis:
2(-1/8)(2 + 2 * 2)(19)(1/8))(3 + 3 * (-2))
---------------------------^
```
- ```(2+55/5)+(2+(2+3+))(19)(1/8)``` 
 ```
Missing Number After Operator:
(2+55/5)+(2+(2+3+))(19)(1/8)
-----------------^
```
- ```2(-1)--(2 + 2 * 2)2(1\8)(3 + 3 *1)``` 
 ```
Illegal Character:
2(-1)--(2 + 2 * 2)2(1\8)(3 + 3 *1)
---------------------^
```


## Building
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
